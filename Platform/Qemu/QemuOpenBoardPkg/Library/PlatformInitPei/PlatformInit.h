#include <PiPei.h>
#include <Uefi.h>

EFI_STATUS
EFIAPI
PlatformInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );

UINT32
EFIAPI
GetMemoryBelow4Gb(
  VOID
);

EFI_STATUS
EFIAPI
InstallMemory (
  IN CONST EFI_PEI_SERVICES  **PeiServices
  );

EFI_STATUS
EFIAPI
InitializePcie (
  VOID
  );

EFI_STATUS
EFIAPI
InitializePciPIIX4 (
  VOID
  );

EFI_STATUS
EFIAPI
MaxCpuInit(
  VOID
);