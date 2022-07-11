#include "PlatformInit.h"
#include <Library/PeimEntryPoint.h>
#include <Library/PeiServicesLib.h>
#include "Library/DebugLib.h"
#include <Library/PlatformInitLib.h>
#include <Library/HobLib.h>
#include <Library/PciCf8Lib.h>
#include <IndustryStandard/Pci.h>
#include <Library/MemoryAllocationLib.h>

EFI_STATUS
EFIAPI
PlatformInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS  Status;
  UINT16 DeviceId;
  EFI_HOB_PLATFORM_INFO *EfiPlatformInfo;

  Status = InstallMemory (PeiServices);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Memory installation failed\n", __FUNCTION__, __LINE__));
    return Status;
  } else {
    DEBUG ((DEBUG_INFO, "Memory installation success\n", __FUNCTION__, __LINE__));
  }

  EfiPlatformInfo = AllocateZeroPool(sizeof(EFI_HOB_PLATFORM_INFO));
  if(EfiPlatformInfo == NULL){
    DEBUG ((DEBUG_ERROR, "Failed to allocate pool for EFI_HOB_PLATFORM_INFO\n"));
    return EFI_UNSUPPORTED;
  }
  DeviceId = PciCf8Read16 (PCI_CF8_LIB_ADDRESS (0, 0, 0, PCI_DEVICE_ID_OFFSET));
  DEBUG ((DEBUG_INFO, "Building gUefiOvmfPkgPlatformInfoGuid with Host bridge dev ID %x \n", DeviceId));
  (*EfiPlatformInfo).HostBridgeDevId = DeviceId;

  BuildGuidDataHob (&gUefiOvmfPkgPlatformInfoGuid, EfiPlatformInfo, sizeof (EFI_HOB_PLATFORM_INFO));

  return EFI_SUCCESS;
}
