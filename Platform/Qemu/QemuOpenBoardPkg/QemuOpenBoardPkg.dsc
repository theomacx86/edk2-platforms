[Defines]

    DSC_SPECIFICATION           = 0x0001001C
    PLATFORM_GUID               = 94797875-D562-40CF-8D55-ADD623C8D46C
    PLATFORM_NAME               = QemuOpenBoardPkg
    PLATFORM_VERSION            = 0.1
    SUPPORTED_ARCHITECTURES     = X64 | IA32
    FLASH_DEFINITION            = $(PLATFORM_NAME)/$(PLATFORM_NAME).fdf
    OUTPUT_DIRECTORY            = Build/$(PLATFORM_NAME)
    BUILD_TARGETS               = DEBUG|RELEASE
    SKUID_IDENTIFIER            = ALL

[SkuIds]
  0|DEFAULT  

[PcdsFixedAtBuild]
gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x8040004F
gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x17
gEfiMdeModulePkgTokenSpaceGuid.PcdHeapGuardPropertyMask|0xFF
gEfiMdeModulePkgTokenSpaceGuid.PcdCpuStackGuard|TRUE
gEfiMdeModulePkgTokenSpaceGuid.PcdHeapGuardPoolType|0x0000000000000002

[PcdsFixedAtBuild.PcdsPatchableInModule]

gMinPlatformPkgTokenSpaceGuid.PcdSmiHandlerProfileEnable|FALSE
gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable |FALSE


!include MinPlatformPkg/Include/Dsc/CoreCommonLib.dsc


[LibraryClasses.X64]
DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
TimerLib|OvmfPkg/Library/AcpiTimerLib/BaseAcpiTimerLibBhyve.inf
PlatformSecLib|UefiCpuPkg/Library/PlatformSecLibNull/PlatformSecLibNull.inf
CpuExceptionHandlerLib|UefiCpuPkg/Library/CpuExceptionHandlerLib/SecPeiCpuExceptionHandlerLib.inf
ReportStatusCodeLib|MdeModulePkg/Library/PeiReportStatusCodeLib/PeiReportStatusCodeLib.inf
HobLib|MdePkg/Library/PeiHobLib/PeiHobLib.inf
MemoryAllocationLib|MdePkg/Library/PeiMemoryAllocationLib/PeiMemoryAllocationLib.inf
VmgExitLib|OvmfPkg/Library/VmgExitLib/SecVmgExitLib.inf
PlatformHookLib|MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf
ExtractGuidedSectionLib|MdePkg/Library/BaseExtractGuidedSectionLib/BaseExtractGuidedSectionLib.inf
MemEncryptSevLib|OvmfPkg/Library/BaseMemEncryptSevLib/SecMemEncryptSevLib.inf
CcProbeLib|OvmfPkg/Library/CcProbeLib/CcProbeLib.inf
ReportFvLib|MinPlatformPkg/PlatformInit/Library/PeiReportFvLib/PeiReportFvLib.inf
TestPointLib|MinPlatformPkg/Test/Library/TestPointLib/PeiTestPointLib.inf
TestPointCheckLib|MinPlatformPkg/Test/Library/TestPointCheckLib/PeiTestPointCheckLib.inf
PciSegmentInfoLib|MinPlatformPkg/Pci/Library/PciSegmentInfoLibSimple/PciSegmentInfoLibSimple.inf
BoardInitLib|MinPlatformPkg/PlatformInit/Library/BoardInitLibNull/BoardInitLibNull.inf
SetCacheMtrrLib|MinPlatformPkg/Library/SetCacheMtrrLib/SetCacheMtrrLib.inf
ReportCpuHobLib|MinPlatformPkg/PlatformInit/Library/ReportCpuHobLib/ReportCpuHobLib.inf

#Silicon doesn't exist in QEMU, NULL libs are sufficient
SiliconPolicyInitLib|MinPlatformPkg/PlatformInit/Library/SiliconPolicyInitLibNull/SiliconPolicyInitLibNull.inf
SiliconPolicyUpdateLib|MinPlatformPkg/PlatformInit/Library/SiliconPolicyUpdateLibNull/SiliconPolicyUpdateLibNull.inf


[LibraryClasses.common.SEC]
DebugLib|OvmfPkg/Library/PlatformDebugLibIoPort/PlatformRomDebugLibIoPort.inf

[LibraryClasses.common.PEI_CORE]
DebugLib|OvmfPkg/Library/PlatformDebugLibIoPort/PlatformDebugLibIoPort.inf

[Components.X64]


#FvPreMemory
#OvmfPkg/Sec/SecMain.inf
UefiCpuPkg/SecCore/SecCore.inf

#OvmfPkg/ResetVector/ResetVector.inf

MinPlatformPkg/PlatformInit/PlatformInitPei/PlatformInitPreMem.inf
MinPlatformPkg/PlatformInit/ReportFv/ReportFvPei.inf
MinPlatformPkg/PlatformInit/SiliconPolicyPei/SiliconPolicyPeiPreMem.inf

#FvFspM
MdeModulePkg/Core/Pei/PeiMain.inf
MdeModulePkg/Universal/PCD/Pei/Pcd.inf

#FvPreMemorySilicon
MdeModulePkg/Universal/ReportStatusCodeRouter/Pei/ReportStatusCodeRouterPei.inf
MdeModulePkg/Universal/StatusCodeHandler/Pei/StatusCodeHandlerPei.inf

SourceLevelDebugPkg/DebugAgentPei/DebugAgentPei.inf
