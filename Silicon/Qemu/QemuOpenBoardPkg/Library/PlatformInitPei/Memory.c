/** @file
  Memory probing and installation

  Copyright (c) 2022 Théo Jehl All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <PlatformInit.h>
#include <Library/DebugLib.h>
#include <Library/OpenQemuFwCfgLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/HobLib.h>

/**
  Return the memory size below 4GB.

  @return UINT32
**/
UINT32
EFIAPI
GetMemoryBelow4Gb (
  VOID
  )
{
  EFI_E820_ENTRY    E820Entry;
  QEMU_FW_CFG_FILE  FwCfgFile;
  UINT32            Processed;
  UINT32            Size;
  EFI_STATUS        Status;

  Status = QemuFwCfgIsPresent ();

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = QemuFwCfgFindFile ("etc/e820", &FwCfgFile);

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Size = 0;
  QemuFwCfgSelectItem (FwCfgFile.select);
  for (Processed = 0; Processed < FwCfgFile.size / sizeof (EFI_E820_ENTRY); Processed++) {
    QemuFwCfgReadBytes (sizeof (EFI_E820_ENTRY), &E820Entry);
    if (E820Entry.BaseAddr + E820Entry.Length < SIZE_4GB) {
      Size += E820Entry.Length;
    } else {
      return Size;
    }
  }

  return Size;
}

/**
  Reserve an MMIO region

  @param Start
  @param Length
**/
STATIC
VOID
ReserveMmioRegion (
  EFI_PHYSICAL_ADDRESS  Start,
  UINT64                Length
  )
{
  EFI_RESOURCE_TYPE            ResourceType;
  EFI_RESOURCE_ATTRIBUTE_TYPE  ResourceAttributes;

  ResourceAttributes = EFI_RESOURCE_ATTRIBUTE_PRESENT | EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE | EFI_RESOURCE_ATTRIBUTE_TESTED;
  ResourceType       = EFI_RESOURCE_MEMORY_MAPPED_IO;

  BuildResourceDescriptorHob (
    ResourceType,
    ResourceAttributes,
    Start,
    Length
    );
}

/**
  Install EFI memory by probing Qemu FW CFG devices for valid E820 entries
  It also reserve space for MMIO regions such as VGA, BIOS and APIC

  @param PeiServices
  @retval EFI_SUCCESS Memory initialization succeded
  @retval EFI_UNSUPPORTED Installation failed (etc/e820 file was not found)
  @retval EFI_NOT_FOUND  Qemu FW CFG device is not present
**/
EFI_STATUS
EFIAPI
InstallMemory (
  IN CONST EFI_PEI_SERVICES  **PeiServices
  )
{
  EFI_STATUS                   Status;
  CONST EFI_PEI_SERVICES       **PeiServicesTable;
  EFI_E820_ENTRY               E820Entry;
  EFI_E820_ENTRY               LargestE820Entry;
  QEMU_FW_CFG_FILE             FwCfgFile;
  UINT32                       Processed;
  BOOLEAN                      ValidMemory;
  EFI_RESOURCE_TYPE            ResourceType;
  EFI_RESOURCE_ATTRIBUTE_TYPE  ResourceAttributes;

  Status = QemuFwCfgIsPresent ();

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "QEMU fw_cfg device is not present\n"));
    return EFI_NOT_FOUND;
  } else {
    DEBUG ((DEBUG_INFO, "QEMU fw_cfg device is present\n"));
  }

  Status = QemuFwCfgFindFile ("etc/e820", &FwCfgFile);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "etc/e820 was not found \n"));
    return EFI_UNSUPPORTED;
  }

  LargestE820Entry.Length = 0;
  QemuFwCfgSelectItem (FwCfgFile.select);
  for (Processed = 0; Processed < FwCfgFile.size / sizeof (EFI_E820_ENTRY); Processed++) {
    QemuFwCfgReadBytes (sizeof (EFI_E820_ENTRY), &E820Entry);

    ValidMemory        = E820Entry.Type == EFI_E820_ENTRY_TYPE_RAM;
    ResourceType       = EFI_RESOURCE_MEMORY_RESERVED;
    ResourceAttributes = EFI_RESOURCE_ATTRIBUTE_PRESENT | EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE | EFI_RESOURCE_ATTRIBUTE_TESTED;

    if (ValidMemory) {
      if ((E820Entry.Length > LargestE820Entry.Length) && (E820Entry.BaseAddr + E820Entry.Length <= SIZE_4GB)) {
        DEBUG ((DEBUG_INFO, "New largest entry for PEI: BaseAddress %lx, Size %lx \n", LargestE820Entry.BaseAddr, LargestE820Entry.Length));
        LargestE820Entry = E820Entry;
      }

      ResourceType       = EFI_RESOURCE_SYSTEM_MEMORY;
      ResourceAttributes = EFI_RESOURCE_ATTRIBUTE_PRESENT |
                           EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
                           EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
                           EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
                           EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
                           EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |
                           EFI_RESOURCE_ATTRIBUTE_TESTED;
      // Lets handle the lower 1MB in a special way
      if (E820Entry.BaseAddr == 0) {
        // 0 - 0xa0000 is system memory
        BuildResourceDescriptorHob (
          ResourceType,
          ResourceAttributes,
          0,
          0xa0000
          );
        E820Entry.BaseAddr += BASE_1MB;
        E820Entry.Length   -= SIZE_1MB;
      }
    }

    BuildResourceDescriptorHob (
      ResourceType,
      ResourceAttributes,
      E820Entry.BaseAddr,
      E820Entry.Length
      );
    DEBUG ((DEBUG_INFO, "Processed base address %lx size %lx type %x\n", E820Entry.BaseAddr, E820Entry.Length, E820Entry.Type));
  }

  ASSERT (LargestE820Entry.Length != 0);
  DEBUG ((DEBUG_INFO, "Largest memory chunk found: address %lx size %lx \n", LargestE820Entry.BaseAddr, LargestE820Entry.Length));

  PeiServicesTable = GetPeiServicesTablePointer ();

  if ((LargestE820Entry.BaseAddr == 0) && (LargestE820Entry.Length >= SIZE_1MB)) {
    // Jump over the first 1MB, since a good chunk of it isn't actually allocatable
    LargestE820Entry.BaseAddr += BASE_1MB;
    LargestE820Entry.Length   -= SIZE_1MB;
  }

  Status = (*PeiServices)->InstallPeiMemory (PeiServicesTable, LargestE820Entry.BaseAddr, LargestE820Entry.Length);

  ASSERT_EFI_ERROR (Status);

  // Reserve architectural PC MMIO regions
  // VGA space + BIOS shadow mapping
  ReserveMmioRegion (0xa0000, 0x100000 - 0xa0000);
  // IO APIC and LAPIC space
  ReserveMmioRegion (0xfec00000, 0xff000000 - 0xfec00000);
  return Status;
}
