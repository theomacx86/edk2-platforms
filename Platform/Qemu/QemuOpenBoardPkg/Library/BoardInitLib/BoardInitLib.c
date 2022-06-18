#include "Library/BoardInitLib.h"

/**
  This board service detects the board type.

  @retval EFI_SUCCESS   The board was detected successfully.
  @retval EFI_NOT_FOUND The board could not be detected.
**/
EFI_STATUS
EFIAPI
BoardDetect (
  VOID
  )
{   
    //Placeholder, must check for PIIX4 / ICH9
    return EFI_SUCCESS;
}

/**
  This board service initializes board-specific debug devices.

  @retval EFI_SUCCESS   Board-specific debug initialization was successful.
  @retval EFI_NOT_READY The board has not been detected yet.
**/
EFI_STATUS
EFIAPI
BoardDebugInit (
  VOID
  )
{
    //placeholder
    return EFI_SUCCESS;
}

EFI_BOOT_MODE
EFIAPI
BoardBootModeDetect (
  VOID
  )
{
    //Placeholder
    return BOOT_WITH_FULL_CONFIGURATION;
}
