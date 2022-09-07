#include "QemuPflash.h"
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>

volatile UINT8 * PflashBasePointer;
UINT16 BlockSize;
UINT32 NvStorageSize;

EFI_STATUS
EFIAPI
QemuPflashInit(
  VOID
)
{
  //
  //  Set pointer to volatile for device access
  //  Avoid compiler optimisation that could return incorrect values
  //
  volatile UINT8 * Pointer;
  UINT8  PreviousValue, Value;
  UINTN Offset;

  PflashBasePointer = (UINT8*) (UINTN) PcdGet32(PcdFlashNvStorageVariableBase);
  BlockSize = (UINT16) PcdGet16(PcdFdVarBlockSize);
  NvStorageSize = PcdGet32(PcdFlashNvStorageVariableSize) + PcdGet32(PcdFlashNvStorageFtwWorkingSize) + PcdGet32(PcdFlashNvStorageFtwSpareSize);

  DEBUG ((DEBUG_INFO, "QemuPflash Size %x, Block size %x, Module %x\n", NvStorageSize, BlockSize, NvStorageSize % BlockSize));

  //
  //  Check that the NV storage flash size is dividible by block size
  //
  ASSERT(NvStorageSize % PcdGet16(PcdFdVarBlockSize) == 0);

  Pointer = PflashBasePointer;

  //
  // Look for first non-0 data withing the first block
  // It must at least contain part of the FD NV header
  // It must also be different from 0x50 and 0x70,
  // two different commands that we will use to determine device behavior
  //

  for(Offset = 0; Offset < PcdGet16(PcdFdVarBlockSize); ++Offset){
    if((*Pointer) != 0 && (*Pointer) != QEMU_PFLASH_CLEAR_STATUS && (*Pointer) != QEMU_PFLASH_STATUS_REGISTER)
    {
      break;
    }
    ++Pointer;
  }

  //
  //  Reached end of block without finding meaningful data, considering absent
  //
  if( (*Pointer) == 0 ){
    DEBUG ((DEBUG_ERROR, "QemuPflash: Device absent (reached end of block without finding data)\n"));
    return EFI_UNSUPPORTED;
  }


  //
  //  The flash device can behave differently based on configuration
  //  For writting, we need the FLASH behavior
  //
  PreviousValue = *Pointer;
  *Pointer = QEMU_PFLASH_CLEAR_STATUS;
  Value = *Pointer;

  if(Value == QEMU_PFLASH_CLEAR_STATUS){
    DEBUG ((DEBUG_ERROR, "QemuPflash: Device behave as RAM\n"));
    *Pointer = PreviousValue;
    return EFI_UNSUPPORTED;
  }
  else{
    *Pointer = QEMU_PFLASH_STATUS_REGISTER;
    if(*Pointer = QEMU_PLASH_CLEARED_ARRAY_STATUS){
      DEBUG ((DEBUG_ERROR, "QemuPflash: Device behave as FLASH\n"));
      return EFI_SUCCESS;
    }
    else{
      DEBUG ((DEBUG_ERROR, "QemuPflash: Device behave as ROM or RAM\n"));
      *Pointer = PreviousValue;
      return EFI_UNSUPPORTED;
    }
  }

  return EFI_SUCCESS;
}

/**
 * @brief Read a byte from the QEMU flash device.
 *
 * @param Offset
 */
UINT8
EFIAPI
QemuPflashReadByte(
  IN UINTN Offset
)
{
  return (UINT8) *(PflashBasePointer+Offset);
}

/**
 * @brief Write a byte to the QEMU flash device.
 *
 * @param Offset
 * @param Value
 * @return EFI_STATUS
 */
VOID
EFIAPI
QemuPflashWriteByte(
  IN UINTN Offset,
  IN UINT8 Value
)
{
  *(PflashBasePointer + Offset) = Value;
}

UINT8 *
EFIAPI
QemuPflashGetBaseAddress(
  VOID
)
{
  return PflashBasePointer;
}

UINT32
EFIAPI
QemuPflashGetSize(
  VOID
)
{
  return NvStorageSize;
}

UINT16
EFIAPI
QemuPflashGetBlockSize(
  VOID
)
{
  return BlockSize;
}