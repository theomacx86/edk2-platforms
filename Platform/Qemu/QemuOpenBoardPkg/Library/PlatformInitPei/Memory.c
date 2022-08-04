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
  EFI_E820_ENTRY          LargestE820Entry;
  QEMU_FW_CFG_FILE        FwCfgFile;
  UINT32                  Processed;

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

  LargestE820Entry.Length = 0;
  QemuFwCfgSelectItem (FwCfgFile.select);
  for (Processed = 0; Processed < FwCfgFile.size / sizeof (EFI_E820_ENTRY); Processed++) {
    QemuFwCfgReadBytes (sizeof (EFI_E820_ENTRY), &E820Entry);
    if (E820Entry.Length > LargestE820Entry.Length && E820Entry.Length + E820Entry.Length <= SIZE_4GB) {
      LargestE820Entry = E820Entry;
    }

    BuildResourceDescriptorHob (
                                EFI_RESOURCE_SYSTEM_MEMORY,
                                EFI_RESOURCE_ATTRIBUTE_PRESENT |
                                EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
                                EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
                                EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
                                EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
                                EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |
                                EFI_RESOURCE_ATTRIBUTE_TESTED,
                                E820Entry.BaseAddr,
                                E820Entry.Length
                                );
    DEBUG ((DEBUG_INFO, "Processed base address %lx size %lx \n", E820Entry.BaseAddr, E820Entry.Length));
  }

  ASSERT (LargestE820Entry.Length != 0);
  DEBUG ((DEBUG_INFO, "Largest memory chunk found: address %lx size %lx \n", LargestE820Entry.BaseAddr, LargestE820Entry.Length));

  PeiServicesTable = GetPeiServicesTablePointer ();

  Status = (*PeiServices)->InstallPeiMemory (PeiServicesTable, LargestE820Entry.BaseAddr, LargestE820Entry.Length);

  ASSERT_EFI_ERROR (Status);

  return Status;
}
