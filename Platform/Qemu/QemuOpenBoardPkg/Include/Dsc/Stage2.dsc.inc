## @file
# Common DSC content to begin Stage 2 enabling
#
# @copyright
# Copyright (C) 2022 Jehl Théo
#
# SPDX-License-Identifier: BSD-2-Clause-Patent
##

[LibraryClasses.common]
  ResetSystemLib|OvmfPkg/Library/ResetSystemLib/BaseResetSystemLib.inf
  PciHostBridgeLib|OvmfPkg/Library/PciHostBridgeLib/PciHostBridgeLib.inf
  PciHostBridgeUtilityLib|OvmfPkg/Library/PciHostBridgeUtilityLib/PciHostBridgeUtilityLib.inf
  DxeHardwareInfoLib|OvmfPkg/Library/HardwareInfoLib/DxeHardwareInfoLib.inf

[LibraryClasses.common.DXE_DRIVER, LibraryClasses.common.DXE_RUNTIME_DRIVER, LibraryClasses.common.DXE_SMM_DRIVER, LibraryClasses.common.UEFI_DRIVER, LibraryClasses.common.UEFI_APPLICATION, LibraryClasses.common.SMM_CORE]
  PciLib|OvmfPkg/Library/DxePciLibI440FxQ35/DxePciLibI440FxQ35.inf

[Components.$(PEI_ARCH)]
  UefiCpuPkg/CpuMpPei/CpuMpPei.inf{
    <LibraryClasses>
    MpInitLib|UefiCpuPkg/Library/MpInitLib/PeiMpInitLib.inf
    TimerLib|OvmfPkg/Library/AcpiTimerLib/BaseAcpiTimerLib.inf
  }
  MinPlatformPkg/PlatformInit/SiliconPolicyPei/SiliconPolicyPeiPostMem.inf
  MinPlatformPkg/PlatformInit/PlatformInitPei/PlatformInitPostMem.inf
  MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf

[Components.$(DXE_ARCH)]
  MdeModulePkg/Universal/ResetSystemRuntimeDxe/ResetSystemRuntimeDxe.inf
  MdeModulePkg/Bus/Pci/PciHostBridgeDxe/PciHostBridgeDxe.inf
  