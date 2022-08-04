#include "PlatformInit.h"
#include <IndustryStandard/Pci.h>
#include <Library/PciCf8Lib.h>
#include <IndustryStandard/Q35MchIch9.h>
#include <Library/OpenQemuFwCfgLib.h>
#include <IndustryStandard/MemoryMappedConfigurationSpaceAccessTable.h>
#include <Library/DebugLib.h>
#include <IndustryStandard/Acpi30.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>

EFI_STATUS
EFIAPI
InitializePcie (
  VOID
  )
{
  union {
    UINT64    Uint64;
    UINT32    Uint32[2];
  } PciExBarBase;

  PciExBarBase.Uint64 = FixedPcdGet64 (PcdPciExpressBaseAddress);

  // Build a reserved memory space for PCIE MMIO
  BuildResourceDescriptorHob (
                              EFI_RESOURCE_MEMORY_RESERVED,
                              EFI_RESOURCE_ATTRIBUTE_PRESENT |
                              EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
                              EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
                              EFI_RESOURCE_ATTRIBUTE_TESTED,
                              PciExBarBase.Uint64,
                              SIZE_256MB
                              );

  BuildMemoryAllocationHob (
                            PciExBarBase.Uint64,
                            SIZE_256MB,
                            EfiReservedMemoryType
                            );

  // Clear register
  PciWrite32 (DRAMC_REGISTER_Q35 (MCH_PCIEXBAR_LOW), 0);

  // Program PCIE MMIO Base address in MCH PCIEXBAR register
  PciWrite32 (DRAMC_REGISTER_Q35 (MCH_PCIEXBAR_HIGH), PciExBarBase.Uint32[1]);
  // Enable 256Mb MMIO space
  PciWrite32 (
              DRAMC_REGISTER_Q35 (MCH_PCIEXBAR_LOW),
              PciExBarBase.Uint32[0] | MCH_PCIEXBAR_BUS_FF | MCH_PCIEXBAR_EN
              );

  // Missing ACPI MCFG

  return EFI_SUCCESS;
}
