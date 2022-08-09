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
InitializePciPIIX4 (
  VOID
  )
{
    UINTN PciIoBase;
    UINTN PciIoSize;

    UINTN PciMmio32Base;
    UINTN PciMmio32Size;

    PciIoBase = 0xC000;
    PciIoSize = 0x4000;

    PcdSet64S(PcdPciIoBase, PciIoBase);
    PcdSet64S(PcdPciIoSize, PciIoSize);

    PciMmio32Base = GetMemoryBelow4Gb();
    if(PciMmio32Base == 0){
        DEBUG ((DEBUG_ERROR, "Unable to detect memory below 4Gb\n"));
        CpuDeadLoop();
        return EFI_UNSUPPORTED;
    }
    DEBUG ((DEBUG_ERROR, "Memory below 4Gb: %x \n", PciMmio32Base));
    PciMmio32Size = 0xFC000000 - PciMmio32Base;

    PcdSet64S(PcdPciMmio32Base, PciMmio32Base);
    PcdSet64S(PcdPciMmio32Size, PciMmio32Size);

    return EFI_SUCCESS;

}