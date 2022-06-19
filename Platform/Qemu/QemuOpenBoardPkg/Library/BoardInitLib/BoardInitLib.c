#include "Library/BoardInitLib.h"
#include "Library/IoLib.h"
#include "Library/PcdLib.h"
#include "Library/DebugLib.h"

#define QEMU_IO_DEBUG_MAGIC  0xE9

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
    DEBUG ((DEBUG_ERROR, "BoardDetect()\n"));
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
    //Return EFI_SUCCESS if QEMU Debug IO ports return magic
    if(IoRead8( PcdGet16(PcdDebugIoPort) ) == QEMU_IO_DEBUG_MAGIC ){
        DEBUG ((DEBUG_ERROR, "QEMU IO Port ready.\n"));
        return EFI_SUCCESS;
    }
    else{
        DEBUG ((DEBUG_ERROR, "QEMU IO Port not ready / misconfigured.\n"));
        return EFI_NOT_READY;
    }
}

EFI_BOOT_MODE
EFIAPI
BoardBootModeDetect (
  VOID
  )
{
    //Placeholder
    DEBUG ((DEBUG_ERROR, "BoardBootModeDetect()\n"));
    return BOOT_WITH_FULL_CONFIGURATION;
}

/**
  A hook for board-specific initialization prior to memory initialization.

  @retval EFI_SUCCESS   The board initialization was successful.
  @retval EFI_NOT_READY The board has not been detected yet.
**/
EFI_STATUS
EFIAPI
BoardInitBeforeMemoryInit (
  VOID
  )
{
    DEBUG ((DEBUG_ERROR, "BoardInitBeforeMemoryInit()\n"));
    return EFI_SUCCESS;
}

/**
  A hook for board-specific initialization after memory initialization.

  @retval EFI_SUCCESS   The board initialization was successful.
  @retval EFI_NOT_READY The board has not been detected yet.
**/
EFI_STATUS
EFIAPI
BoardInitAfterMemoryInit (
  VOID
  )
{
    DEBUG ((DEBUG_ERROR, "BoardInitAfterMemoryInit()\n"));
    return EFI_SUCCESS;
}

/**
  A hook for board-specific initialization prior to disabling temporary RAM.

  @retval EFI_SUCCESS   The board initialization was successful.
  @retval EFI_NOT_READY The board has not been detected yet.
**/
EFI_STATUS
EFIAPI
BoardInitBeforeTempRamExit (
  VOID
  )
{
    DEBUG ((DEBUG_ERROR, "BoardInitBeforeTempRamExit()\n"));
    return EFI_SUCCESS;
}

/**
  A hook for board-specific initialization after disabling temporary RAM.

  @retval EFI_SUCCESS   The board initialization was successful.
  @retval EFI_NOT_READY The board has not been detected yet.
**/
EFI_STATUS
EFIAPI
BoardInitAfterTempRamExit (
  VOID
  )
{
    DEBUG ((DEBUG_ERROR, "BoardInitAfterTempRamExit()\n"));
    return EFI_SUCCESS;
}

/**
  A hook for board-specific initialization prior to silicon initialization.

  @retval EFI_SUCCESS   The board initialization was successful.
  @retval EFI_NOT_READY The board has not been detected yet.
**/
EFI_STATUS
EFIAPI
BoardInitBeforeSiliconInit (
  VOID
  )
{
    DEBUG ((DEBUG_ERROR, "BoardInitBeforeSiliconInit()\n"));
    return EFI_SUCCESS;
}

/**
  A hook for board-specific initialization after silicon initialization.

  @retval EFI_SUCCESS   The board initialization was successful.
  @retval EFI_NOT_READY The board has not been detected yet.
**/
EFI_STATUS
EFIAPI
BoardInitAfterSiliconInit (
  VOID
  )
{
    DEBUG ((DEBUG_ERROR, "BoardInitAfterSiliconInit()\n"));
    return EFI_SUCCESS;
}

/**
  A hook for board-specific initialization after PCI enumeration.

  @retval EFI_SUCCESS   The board initialization was successful.
  @retval EFI_NOT_READY The board has not been detected yet.
**/
EFI_STATUS
EFIAPI
BoardInitAfterPciEnumeration (
  VOID
  )
{
    DEBUG ((DEBUG_ERROR, "BoardInitAfterPciEnumeration()\n"));
    return EFI_SUCCESS;
}

/**
  A hook for board-specific functionality for the ReadyToBoot event.

  @retval EFI_SUCCESS   The board initialization was successful.
  @retval EFI_NOT_READY The board has not been detected yet.
**/
EFI_STATUS
EFIAPI
BoardInitReadyToBoot (
  VOID
  )
{
    DEBUG ((DEBUG_ERROR, "BoardInitReadyToBoot()\n"));
    return EFI_SUCCESS;
}

/**
  A hook for board-specific functionality for the ExitBootServices event.

  @retval EFI_SUCCESS   The board initialization was successful.
  @retval EFI_NOT_READY The board has not been detected yet.
**/
EFI_STATUS
EFIAPI
BoardInitEndOfFirmware (
  VOID
  )
{
    DEBUG ((DEBUG_ERROR, "BoardInitEndOfFirmware()\n"));
    return EFI_SUCCESS;
}
