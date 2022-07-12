## @file
# Common DSC content to begin Stage 1 enabling
#
# @copyright
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: BSD-2-Clause-Patent
##

[PcdsFixedAtBuild.IA32]
  ## MinPlatform Boot Stage Selector
  # Stage 1 - enable debug (system deadloop after debug init)
  # Stage 2 - mem init (system deadloop after mem init)
  # Stage 3 - boot to shell only
  # Stage 4 - boot to OS
  # Stage 5 - boot to OS with security boot enabled
  # Stage 6 - boot with advanced features enabled
  #
  

  #
  # Enable stack and heap protections
  #
  #gEfiMdeModulePkgTokenSpaceGuid.PcdHeapGuardPropertyMask|0xFF
  #gEfiMdeModulePkgTokenSpaceGuid.PcdCpuStackGuard|TRUE

################################################################################
#
# Library Class section - list of all Library Classes needed by this Platform.
#
################################################################################

[LibraryClasses]
  PciSegmentInfoLib|MinPlatformPkg/Pci/Library/PciSegmentInfoLibSimple/PciSegmentInfoLibSimple.inf
  #BoardInitLib|MinPlatformPkg/PlatformInit/Library/BoardInitLibNull/BoardInitLibNull.inf
  BoardInitLib|QemuOpenBoardPkg/Library/BoardInitLib/BoardInitLib.inf
  SetCacheMtrrLib|MinPlatformPkg/Library/SetCacheMtrrLib/SetCacheMtrrLib.inf
  ReportCpuHobLib|MinPlatformPkg/PlatformInit/Library/ReportCpuHobLib/ReportCpuHobLib.inf
  SiliconPolicyInitLib|MinPlatformPkg/PlatformInit/Library/SiliconPolicyInitLibNull/SiliconPolicyInitLibNull.inf
  SiliconPolicyUpdateLib|MinPlatformPkg/PlatformInit/Library/SiliconPolicyUpdateLibNull/SiliconPolicyUpdateLibNull.inf
  ReportFvLib|QemuOpenBoardPkg/Library/PeiReportFvLib/PeiReportFvLib.inf

[LibraryClasses.Common.SEC]
  TestPointCheckLib|MinPlatformPkg/Test/Library/TestPointCheckLib/SecTestPointCheckLib.inf
  TimerLib|MdePkg/Library/BaseTimerLibNullTemplate/BaseTimerLibNullTemplate.inf

[LibraryClasses.Common.PEI_CORE, LibraryClasses.Common.PEIM]
  TestPointCheckLib|MinPlatformPkg/Test/Library/TestPointCheckLib/PeiTestPointCheckLib.inf
  TestPointLib|MinPlatformPkg/Test/Library/TestPointLib/PeiTestPointLib.inf
  TimerLib|MdePkg/Library/BaseTimerLibNullTemplate/BaseTimerLibNullTemplate.inf

[LibraryClasses.common.DXE_CORE, LibraryClasses.common.DXE_SMM_DRIVER, LibraryClasses.common.SMM_CORE, LibraryClasses.common.DXE_DRIVER, LibraryClasses.common.DXE_RUNTIME_DRIVER, LibraryClasses.common.UEFI_DRIVER, LibraryClasses.common.UEFI_APPLICATION]
  TestPointCheckLib|MinPlatformPkg/Test/Library/TestPointCheckLibNull/TestPointCheckLibNull.inf
  TestPointLib|MinPlatformPkg/Test/Library/TestPointLib/DxeTestPointLib.inf

[LibraryClasses.Common.DXE_SMM_DRIVER]
  TestPointCheckLib|MinPlatformPkg/Test/Library/TestPointCheckLib/SmmTestPointCheckLib.inf
  TestPointLib|MinPlatformPkg/Test/Library/TestPointLib/SmmTestPointLib.inf

[Components.IA32]

  UefiCpuPkg/SecCore/SecCore.inf

  MdeModulePkg/Core/Pei/PeiMain.inf

  MdeModulePkg/Universal/Variable/Pei/VariablePei.inf
  UefiCpuPkg/CpuIoPei/CpuIoPei.inf
  MdeModulePkg/Universal/PcatSingleSegmentPciCfg2Pei/PcatSingleSegmentPciCfg2Pei.inf
  MdeModulePkg/Universal/FaultTolerantWritePei/FaultTolerantWritePei.inf

  MdeModulePkg/Universal/PCD/Pei/Pcd.inf  {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  }
  MdeModulePkg/Universal/ReportStatusCodeRouter/Pei/ReportStatusCodeRouterPei.inf
  MdeModulePkg/Universal/StatusCodeHandler/Pei/StatusCodeHandlerPei.inf

  MinPlatformPkg/PlatformInit/PlatformInitPei/PlatformInitPreMem.inf
  MinPlatformPkg/PlatformInit/ReportFv/ReportFvPei.inf
  MinPlatformPkg/PlatformInit/SiliconPolicyPei/SiliconPolicyPeiPreMem.inf

  MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf

  QemuOpenBoardPkg/Library/PlatformInitPei/PlatformInitPei.inf

  