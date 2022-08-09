#include "PlatformInit.h"
#include <IndustryStandard/Pci.h>
#include <Library/PciCf8Lib.h>
#include <Library/OpenQemuFwCfgLib.h>
#include <IndustryStandard/MemoryMappedConfigurationSpaceAccessTable.h>
#include <Library/DebugLib.h>
#include <IndustryStandard/Acpi30.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>

EFI_STATUS
EFIAPI
MaxCpuInit(
  VOID
)
{
    UINT16 BootCpuCount;

    QemuFwCfgSelectItem(5);
    QemuFwCfgReadBytes(sizeof(BootCpuCount), &BootCpuCount);

    DEBUG ((DEBUG_ERROR, "BOOT CPU COUNT %u \n", BootCpuCount));

    PcdSet32S(PcdCpuBootLogicalProcessorNumber, BootCpuCount);

    //PLACEHOLDER
    PcdSet32S(PcdCpuMaxLogicalProcessorNumber, 64);

    return EFI_SUCCESS;
}