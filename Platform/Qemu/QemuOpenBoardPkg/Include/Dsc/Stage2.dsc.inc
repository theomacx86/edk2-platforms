## @file
# Common DSC content to begin Stage 2 enabling
#
# @copyright
# Copyright (C) 2022 Théo Jehl
#
# SPDX-License-Identifier: BSD-2-Clause-Patent
##

[LibraryClasses.Common]
  ResetSystemLib          | OvmfPkg/Library/ResetSystemLib/BaseResetSystemLib.inf
  PciHostBridgeLib        | OvmfPkg/Library/PciHostBridgeLib/PciHostBridgeLib.inf
  PciHostBridgeUtilityLib | OvmfPkg/Library/PciHostBridgeUtilityLib/PciHostBridgeUtilityLib.inf
  DxeHardwareInfoLib      | OvmfPkg/Library/HardwareInfoLib/DxeHardwareInfoLib.inf

[LibraryClasses.Common.PEIM]
  MpInitLib               | UefiCpuPkg/Library/MpInitLib/PeiMpInitLib.inf
  TimerLib                | OvmfPkg/Library/AcpiTimerLib/BaseAcpiTimerLib.inf

[Components.$(PEI_ARCH)]
  UefiCpuPkg/CpuMpPei/CpuMpPei.inf
  MinPlatformPkg/PlatformInit/SiliconPolicyPei/SiliconPolicyPeiPostMem.inf
  MinPlatformPkg/PlatformInit/PlatformInitPei/PlatformInitPostMem.inf
  MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf
