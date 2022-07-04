#include <PiPei.h>
#include <Uefi.h>

EFI_STATUS
EFIAPI
PlatformInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );

EFI_STATUS
EFIAPI
InstallMemory (
  IN CONST EFI_PEI_SERVICES  **PeiServices
  );
