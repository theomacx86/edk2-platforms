#include "QemuOpenFvbService.h"
#include <Library/PcdLib.h>
#include <QemuPflash.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>


EFI_STATUS
EFIAPI
InitializeFvb(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
)
{
  if(!EFI_ERROR(QemuPflashInit()) ){
    DEBUG ((DEBUG_INFO, "QEMU Pflash device was detected.\n"));
  }
  else{
    DEBUG ((DEBUG_ERROR, "Error: QEMU Pflash device was not detected.\n"));
  }

  //
  //  Do not initialize driver is emulated variable store is enabled.
  //
  if(PcdGetBool(PcdEmuVariableNvModeEnable)){
    return EFI_UNSUPPORTED;
  }



  return EFI_SUCCESS;
}