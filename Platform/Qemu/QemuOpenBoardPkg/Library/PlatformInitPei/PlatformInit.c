#include "PlatformInit.h"
#include <Library/PeimEntryPoint.h>
#include <Library/PeiServicesLib.h>

EFI_STATUS
EFIAPI
PlatformInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
    EFI_STATUS Status;
    Status = InstallMemory(PeiServices);
    if(EFI_ERROR(Status)){
      return Status;
    }
    return EFI_SUCCESS;
}