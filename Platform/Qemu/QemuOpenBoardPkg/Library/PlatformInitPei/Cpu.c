/** @file
  CPU Count initialization

  Copyright (c) 2022 Théo Jehl All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include "PlatformInit.h"
#include <IndustryStandard/Pci.h>
#include <Library/PciCf8Lib.h>
#include <Library/OpenQemuFwCfgLib.h>
#include <IndustryStandard/QemuFwCfg.h>
#include <IndustryStandard/MemoryMappedConfigurationSpaceAccessTable.h>
#include <Library/DebugLib.h>
#include <IndustryStandard/Acpi30.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>

/**
  Probe Qemu FW CFG device for current CPU count and report to MpInitLib

  @return EFI_SUCCESS Detection was successful
  @retval EFI_UNSUPPORTED Qemu FW CFG device is not present
 */
EFI_STATUS
EFIAPI
MaxCpuInit (
  VOID
  )
{
  UINT16      BootCpuCount;
  EFI_STATUS  Status;

  Status = QemuFwCfgIsPresent ();

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "QemuFwCfg not present, unable to detect CPU count \n"));
    CpuDeadLoop ();
    return EFI_UNSUPPORTED;
  }
  
  Status = QemuFwCfgSelectItem (QemuFwCfgItemSmpCpuCount);

  if (EFI_ERROR (Status)) {
    return Status;
  }

  QemuFwCfgReadBytes (sizeof (BootCpuCount), &BootCpuCount);

  PcdSet32S (PcdCpuBootLogicalProcessorNumber, BootCpuCount);

  PcdSet32S (PcdCpuMaxLogicalProcessorNumber, 64);

  return EFI_SUCCESS;
}
