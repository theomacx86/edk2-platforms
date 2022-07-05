#include "PlatformInit.h"
#include <Library/PeimEntryPoint.h>
#include <Library/PeiServicesLib.h>
#include "Library/DebugLib.h"

EFI_STATUS
EFIAPI
PlatformInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS  Status;

  UINT64 TestValue;
  TestValue = 0x8000000000000; // 2 251 799 813 685 248
  DEBUG ((DEBUG_INFO, "UINT64 z test %zu, %zx  \n", TestValue, TestValue));


  Status = InstallMemory (PeiServices);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Memory installation failed\n", __FUNCTION__, __LINE__));
    return Status;
  } else {
    DEBUG ((DEBUG_INFO, "Memory installation success\n", __FUNCTION__, __LINE__));
  }

  return EFI_SUCCESS;
}
