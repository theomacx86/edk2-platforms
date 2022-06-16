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

[PcdsFixedAtBuild.PcdsPatchableInModule]
gMinPlatformPkgTokenSpaceGuid.PcdSmiHandlerProfileEnable|FALSE
gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable |FALSE


!include MinPlatformPkg/Include/Dsc/CoreCommonLib.dsc

[LibraryClasses.IA32]
DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf

[LibraryClasses.X64]

[LibraryClasses.common.SEC]

PlatformSecLib|UefiCpuPkg/Library/PlatformSecLibNull/PlatformSecLibNull.inf
CpuExceptionHandlerLib|UefiCpuPkg/Library/CpuExceptionHandlerLib/Xcode5SecPeiCpuExceptionHandlerLib.inf
ReportStatusCodeLib|MdePkg/Library/BaseReportStatusCodeLibNull/BaseReportStatusCodeLibNull.inf
HobLib|MdeModulePkg/Library/BaseHobLibNull/BaseHobLibNull.inf
MemoryAllocationLib|MdeModulePkg/Library/BaseMemoryAllocationLibNull/BaseMemoryAllocationLibNull.inf
VmgExitLib|UefiCpuPkg/Library/VmgExitLibNull/VmgExitLibNull.inf
PlatformHookLib|MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf
ExtractGuidedSectionLib|MdePkg/Library/BaseExtractGuidedSectionLib/BaseExtractGuidedSectionLib.inf
MemEncryptSevLib|OvmfPkg/Library/BaseMemEncryptSevLib/SecMemEncryptSevLib.inf
CcProbeLib|MdePkg/Library/CcProbeLibNull/CcProbeLibNull.inf
[Components.X64]
#UefiCpuPkg/SecCore/SecCore.inf
OvmfPkg/Sec/SecMain.inf
OvmfPkg/ResetVector/ResetVector.inf

