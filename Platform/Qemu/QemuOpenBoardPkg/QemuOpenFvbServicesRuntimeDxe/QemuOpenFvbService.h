#ifndef QEMU_OPEN_FVB_SERVICE_H
#define QEMU_OPEN_FVB_SERVICE_H

#include <Uefi.h>
#include <Library/UefiDriverEntryPoint.h>

EFI_STATUS
EFIAPI
InitializeFvb(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
);

EFI_STATUS
EFIAPI
QemuGetAttributes(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  OUT       EFI_FVB_ATTRIBUTES_2                *Attributes
);

EFI_STATUS
QemuSetAttributes(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN OUT    EFI_FVB_ATTRIBUTES_2                *Attributes
  );

EFI_STATUS
QemuGetPhysicalAddress(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  OUT       EFI_PHYSICAL_ADDRESS                *Address
  );

EFI_STATUS
EFIAPI
QemuGetBlockSize(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN        EFI_LBA                             Lba,
  OUT       UINTN                               *BlockSize,
  OUT       UINTN                               *NumberOfBlocks
  );

EFI_STATUS
EFIAPI
QemuFvbRead(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN        EFI_LBA                             Lba,
  IN        UINTN                               Offset,
  IN OUT    UINTN                               *NumBytes,
  IN OUT    UINT8                               *Buffer
  );

EFI_STATUS
EFIAPI
QemuFvbWrite(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN        EFI_LBA                             Lba,
  IN        UINTN                               Offset,
  IN OUT    UINTN                               *NumBytes,
  IN        UINT8                               *Buffer
  );

EFI_STATUS
EFIAPI
QemuFvbEraseBlock(
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  ...
  );
#endif