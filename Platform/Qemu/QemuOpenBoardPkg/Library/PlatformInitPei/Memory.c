#include "PlatformInit.h"
#include "Library/DebugLib.h"
#include "Library/QemuFwCfgLib.h"
#include <Library/PeiServicesTablePointerLib.h>

EFI_STATUS
EFIAPI
InstallMemory(
    IN CONST EFI_PEI_SERVICES **PeiServices
)
{   
    EFI_STATUS Status;
    CONST EFI_PEI_SERVICES **PeiServicesTable;
    EFI_E820_ENTRY E820Entry;
    QEMU_FW_CFG_FILE FwCfgFile;
    UINT64 BaseAddress = 0;
    UINT64 Size = 0;
    UINT32 Processed;

    //TODO
    /*
        Handle memory installation without Qemu fw_cfg device
    */
    Status = QemuFwCfg_IsPresent();
    if(EFI_ERROR(Status)){
        DEBUG ((DEBUG_INFO, "QEMU fw_cfg device is not present\n", __FUNCTION__, __LINE__));
    }
    else{
        DEBUG ((DEBUG_INFO, "QEMU fw_cfg device is present\n", __FUNCTION__, __LINE__));
    }

    Status = QemuFwCfg_FindFile("etc/e820", &FwCfgFile);
    if(EFI_ERROR(Status)){
        DEBUG ((DEBUG_ERROR, "etc/e820 was not found \n", __FUNCTION__, __LINE__));
    }

    /* TODO
     Verify memory type
     Memory might not be contiguous (really tho?)
    */
    QemuFwCfg_SelectItem(FwCfgFile.select);
    for(Processed = 0; Processed < FwCfgFile.size / sizeof(EFI_E820_ENTRY); Processed++){
        QemuFwCfg_ReadBytes(sizeof(EFI_E820_ENTRY), &E820Entry);
        if(E820Entry.BaseAddr < BaseAddress){
            BaseAddress = E820Entry.BaseAddr;
        }
        Size += E820Entry.Length;
    }
    
    //32 Bits mode
    PeiServicesTable = GetPeiServicesTablePointer();
    DEBUG ((DEBUG_INFO, "Installing memory\nBase address: %Lx\nSize (32 bits): %x\nSize (64 bits):%Lx\n",BaseAddress, (UINT32) Size, (UINT64) Size));
    Status = (*PeiServices)->InstallPeiMemory( PeiServicesTable, (EFI_PHYSICAL_ADDRESS) BaseAddress, (UINT32) Size);
    return Status;
}