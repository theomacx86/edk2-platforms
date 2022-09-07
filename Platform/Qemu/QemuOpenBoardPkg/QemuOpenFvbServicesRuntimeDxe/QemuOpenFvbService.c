#include "QemuOpenFvbService.h"
#include <Library/PcdLib.h>
#include <QemuPflash.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>

#include <Protocol/DevicePath.h>
#include <Protocol/FirmwareVolumeBlock.h>


EFI_FVB_ATTRIBUTES_2 QemuFvbAttributes2;

EFI_FW_VOL_BLOCK_DEVICE QemuFvbBlockDevice = {
  FVB_DEVICE_SIGNATURE,
  NULL,
  0,
  {
    QemuGetAttributes,
    QemuSetAttributes,
    QemuGetPhysicalAddress,
    QemuGetBlockSize,
    QemuFvbRead,
    QemuFvbWrite,
    QemuFvbEraseBlock,
    NULL
  }
}

EFI_STATUS
EFIAPI
QemuGetAttributes(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  OUT       EFI_FVB_ATTRIBUTES_2                *Attributes
)
{
  (*Attributes) = QemuFvbAttributes2;
  return EFI_SUCCESS;
}

EFI_STATUS
QemuSetAttributes(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN OUT    EFI_FVB_ATTRIBUTES_2                *Attributes
  )
{
  QemuFvbAttributes2 = *(Attributes);
  return EFI_SUCCESS;
}

EFI_STATUS
QemuGetPhysicalAddress(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  OUT       EFI_PHYSICAL_ADDRESS                *Address
  )
{
  (*Address) = (EFI_PHYSICAL_ADDRESS) (UINTN) QemuPflashGetBaseAddress();
}

EFI_STATUS
EFIAPI
QemuGetBlockSize(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN        EFI_LBA                             Lba,
  OUT       UINTN                               *BlockSize,
  OUT       UINTN                               *NumberOfBlocks
  )
{
  //
  //  Logical block should not exceed maximul nv flash capacity
  //
  if(Lba * QemuPflashGetBlockSize() >= QemuPflashGetSize()){
    *BlockSize = 0;
    *NumberOfBlocks = 0;
    return EFI_UNSUPPORTED;
  }
  //
  //  In this device, all blocks are the same size
  //
  else{
    *BlockSize = (UINTN) QemuPflashGetBlockSize();
    *NumberOfBlocks = (UINTN) (QemuPflashGetSize() / QemuPflashGetBlockSize() - Lba);
  }
}

EFI_STATUS
EFIAPI
QemuFvbRead(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN        EFI_LBA                             Lba,
  IN        UINTN                               Offset,
  IN OUT    UINTN                               *NumBytes,
  IN OUT    UINT8                               *Buffer
  )
{
  UINTN Processed;
  UINT8 * BaseAddress;

  //
  //  Out of bounds reading
  //
  if(Lba * QemuPflashGetBlockSize() + Offset + NumBytes >= QemuPflashGetSize()){
    *NumBytes = 0;
    return EFI_UNSUPPORTED;
  }

  for(Processed = 0; Processed < *NumBytes; ++Processed){
    Buffer[Processed] = (UINT8) QemuPflashReadByte(Lba * QemuPflashGetBlockSize() + Offset + Processed);
  }

  *NumBytes = Processed;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
QemuFvbWrite(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN        EFI_LBA                             Lba,
  IN        UINTN                               Offset,
  IN OUT    UINTN                               *NumBytes,
  IN        UINT8                               *Buffer
  )
{
  UINTN Processed;

  //
  //  Out of bounds writing
  //
  if(Lba * QemuPflashGetBlockSize() + Offset + NumBytes >= QemuPflashGetSize()){
    *NumBytes = 0;
    return EFI_UNSUPPORTED;
  }

  for(Processed = 0; Processed < *NumBytes; ++Processed){
    QemuPflashWriteByte(Lba * QemuPflashGetBlockSize() + Offset + Processed, QEMU_PFLASH_WRITE_BYTE);
    QemuPflashWriteByte(Lba * QemuPflashGetBlockSize() + Offset + Processed, Buffer[Processed]);
  }

  *NumBytes = Processed;

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
QemuFvbEraseBlock(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  ...
  )
{
  VA_LIST Args;
  EFI_LBA StartingLba;
  UINTN NumberOfBlocks;
  UINTN Processed;

  VA_START(Args, This);

  StartingLba = VA_ARG(Args, EFI_LBA);

  if(StartingLba == EFI_LBA_LIST_TERMINATOR){
    DEBUG ((DEBUG_INFO, "Empty list, no deletion\n"));
    return EFI_SUCCESS;
  }

  while(StartingLba != EFI_LBA_LIST_TERMINATOR){
    NumberOfBlocks = VA_ARG(Args, UINTN);

    //
    //  Check that deletion does not overflow from device
    //

    if( (StartingLba+NumberOfBlocks) * QemuPflashGetBlockSize() >= QemuPflashGetSize()){
      DEBUG ((DEBUG_ERROR, "Out of bounds deletion.. \n"));
      return EFI_INVALID_PARAMETER;
    }

    for(Processed = 0; Processed < NumberOfBlocks; ++Processed){
      QemuPflashWriteByte((StartingLba + NumberOfBlocks) * QemuPflashGetBlockSize(), QEMU_PFLASH_ERASE_BLOCK);
      QemuPflashWriteByte((StartingLba + NumberOfBlocks) * QemuPflashGetBlockSize(), QEMU_PFLASH_ERASE_BLOCK_CONFIRM);
    }

    StartingLba = VA_ARG(Args, UINTN);
  }

  return EFI_SUCCESS;
}

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

  QemuFvbAttributes2 = AllocateZeroPool(sizeof(EFI_FVB_ATTRIBUTES_2));
  if(QemuFvbAttributes2){
    DEBUG ((DEBUG_ERROR, "Unable to allocate pool for QEMU EFI_FVB_ATTRIBUTES_2 \n"));
    return EFI_UNSUPPORTED;
  }



  return EFI_SUCCESS;
}