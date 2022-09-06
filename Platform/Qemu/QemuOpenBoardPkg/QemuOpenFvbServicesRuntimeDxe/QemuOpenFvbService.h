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


#endif