#include "Library/QemuFwCfgLib.h"
#include "Library/BaseMemoryLib.h"
#include "Library/DebugLib.h"

UINT8
EFIAPI
QemuFwCfg_Read8()
{
    return IoRead8(FW_CFG_PORT_DATA);
}

EFI_STATUS
EFIAPI
QemuFwCfg_SelectItem(
    IN UINT16 Selector
)
{
    UINT16 WritenSelector;
    WritenSelector = IoWrite16(FW_CFG_PORT_SEL, Selector);

    if(WritenSelector != Selector){
        return EFI_UNSUPPORTED;
    }
    
    return EFI_SUCCESS;
}

VOID
EFIAPI
QemuFwCfg_ReadBytes(
    IN UINTN Size, 
    OUT VOID* Buffer
)
{
    IoReadFifo8(FW_CFG_PORT_DATA, Size, Buffer);
}

EFI_STATUS
EFIAPI
QemuFwCfg_IsPresent()
{
    EFI_STATUS Status;
    CHAR8 Control[4];

    Status = QemuFwCfg_SelectItem(FW_CFG_SIGNATURE);
    if(EFI_ERROR(Status)){
        return Status;
    }

    QemuFwCfg_ReadBytes(4, &Control);
    if(AsciiStrnCmp( (CHAR8*) &Control, FW_CFG_QEMU_SIGNATURE, 4) != 0){
        return EFI_UNSUPPORTED;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
QemuFwCfg_FindFile(
    IN CHAR8        *String,
    OUT QEMU_FW_CFG_FILE   *FWConfigFile
)
{
    QEMU_FW_CFG_FILE FirmwareConfigFile;
    UINT32 FilesCount;
    UINT32 Idx;
    
    QemuFwCfg_SelectItem(FW_CFG_FILE_DIR);
    QemuFwCfg_ReadBytes(sizeof(UINT32), &FilesCount);

    FilesCount = SwapBytes32(FilesCount);

    for(Idx = 0; Idx < FilesCount; Idx++){
        QemuFwCfg_ReadBytes(sizeof(QEMU_FW_CFG_FILE), &FirmwareConfigFile);
        if(AsciiStrCmp((CHAR8*) &(FirmwareConfigFile.name), String) == 0){
            FirmwareConfigFile.select = SwapBytes16(FirmwareConfigFile.select);
            FirmwareConfigFile.size = SwapBytes32(FirmwareConfigFile.size);
            CopyMem(FWConfigFile, &FirmwareConfigFile, sizeof(QEMU_FW_CFG_FILE));
            return EFI_SUCCESS;
        }
    }

    return EFI_UNSUPPORTED;
}
