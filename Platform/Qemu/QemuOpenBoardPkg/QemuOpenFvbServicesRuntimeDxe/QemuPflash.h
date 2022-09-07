#ifndef QEMU_PFLASH_H
#define QEMU_PFLASH_H

#include <Uefi.h>
#include <Protocol/FirmwareVolumeBlock.h>

//
//  Qemu PFLASH commands
//  Can be found in hw/block/pflash_cfi01.c
//

#define QEMU_PFLASH_WRITE_BYTE          0x10
#define QEMU_PFLASH_ERASE_BLOCK         0x20
#define QEMU_PFLASH_ERASE_BLOCK_CONFIRM 0xd0
#define QEMU_PFLASH_CLEAR_STATUS        0x50
#define QEMU_PFLASH_UNLOCK_BLOCK        0x60
#define QEMU_PFLASH_STATUS_REGISTER     0x70
#define QEMU_PFLASH_WRITE_BLOCK         0xe8
#define QEMU_PFLASH_DEVICE_ID           0x90
#define QEMU_PFLASH_READ_ARRAY          0xFF
#define QEMU_PLASH_CLEARED_ARRAY_STATUS 0x00

/**
  Probe and initialize Qemu Pflash device

  @return EFI_STATUS
**/
EFI_STATUS
EFIAPI
QemuPflashInit(
  VOID
);

EFI_STATUS
EFIAPI
QemuPflashRead(
  IN UINTN Offset,
  IN UINTN Size,
  IN OUT UINTN * Buffer
);

EFI_STATUS
EFIAPI
QemuPflashWrite(
  IN UINTN Offset,
  IN UINTN Size,
  IN OUT UINTN * Buffer
);

UINT8
EFIAPI
QemuPflashReadByte(
  IN UINTN Offset
);

VOID
EFIAPI
QemuPflashWriteByte(
  IN UINTN Offset,
  IN UINT8 Value
);

UINT8 *
EFIAPI
QemuPflashGetBaseAddress(
  VOID
);

UINT32
EFIAPI
QemuPflashGetSize(
  VOID
);

UINT16
EFIAPI
QemuPflashGetBlockSize(
  VOID
);



#endif