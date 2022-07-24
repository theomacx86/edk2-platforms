#include <PlatformInit.h>
#include <Library/DebugLib.h>
#include <Library/OpenQemuFwCfgLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/HobLib.h>

EFI_STATUS
EFIAPI
InstallMemory (
  IN CONST EFI_PEI_SERVICES  **PeiServices
  )
{
  EFI_STATUS              Status;
  CONST EFI_PEI_SERVICES  **PeiServicesTable;
  EFI_E820_ENTRY          E820Entry;
  QEMU_FW_CFG_FILE        FwCfgFile;
  UINT64                  BaseAddress = 0;
  UINT64                  Size        = 0;
  UINT32                  Processed;

  // TODO

  /*
      Handle memory installation without Qemu fw_cfg device
  */
  Status = QemuFwCfgIsPresent ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "QEMU fw_cfg device is not present\n", __FUNCTION__, __LINE__));
  } else {
    DEBUG ((DEBUG_INFO, "QEMU fw_cfg device is present\n", __FUNCTION__, __LINE__));
  }

  Status = QemuFwCfgFindFile ("etc/e820", &FwCfgFile);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "etc/e820 was not found \n", __FUNCTION__, __LINE__));
  }

  /* TODO
   Verify memory type
   Memory might not be contiguous (really tho?)
  */
  QemuFwCfgSelectItem (FwCfgFile.select);
  for (Processed = 0; Processed < FwCfgFile.size / sizeof (EFI_E820_ENTRY); Processed++) {
    QemuFwCfgReadBytes (sizeof (EFI_E820_ENTRY), &E820Entry);
    if (E820Entry.BaseAddr < BaseAddress) {
      BaseAddress = E820Entry.BaseAddr;
    }

    Size += E820Entry.Length;
  }

  PeiServicesTable = GetPeiServicesTablePointer ();

  DEBUG ((DEBUG_INFO, "Installing memory\nBase address: %Lx\nSize: %x\n", BaseAddress, Size));
  Status = (*PeiServices)->InstallPeiMemory (PeiServicesTable, (EFI_PHYSICAL_ADDRESS)BaseAddress + 0x100000, Size - 0x100000);

  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "Declaring system memory HOB\n"));

  BuildResourceDescriptorHob (
    EFI_RESOURCE_SYSTEM_MEMORY,
    EFI_RESOURCE_ATTRIBUTE_PRESENT |
    EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
    EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
    EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
    EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
    EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |
    EFI_RESOURCE_ATTRIBUTE_TESTED,
    0,
    0xa0000
    );
  // Declare system memory
  BuildResourceDescriptorHob (
    EFI_RESOURCE_SYSTEM_MEMORY,
    EFI_RESOURCE_ATTRIBUTE_PRESENT |
    EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
    EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
    EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
    EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
    EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |
    EFI_RESOURCE_ATTRIBUTE_TESTED,
    0x100000,
    Size - 0x100000
    );
 #if 0
  BuildResourceDescriptorHob (
    EFI_RESOURCE_MEMORY_MAPPED_IO,
    EFI_RESOURCE_ATTRIBUTE_PRESENT     |
    EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
    EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
    EFI_RESOURCE_ATTRIBUTE_TESTED,
    0xa0000,
    0x100000 - 0xa0000
    );
  BuildResourceDescriptorHob (
    EFI_RESOURCE_MEMORY_MAPPED_IO,
    EFI_RESOURCE_ATTRIBUTE_PRESENT     |
    EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
    EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
    EFI_RESOURCE_ATTRIBUTE_TESTED,
    0xFEC00000,
    0x3000
    );
 #endif
  return Status;
}
