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

[LibraryClasses.X64]

[LibraryClasses.common.SEC]
DebugLib|OvmfPkg/Library/PlatformDebugLibIoPort/PlatformRomDebugLibIoPort.inf
ExtractGuidedSectionLib|MdePkg/Library/BaseExtractGuidedSectionLib/BaseExtractGuidedSectionLib.inf
MemEncryptSevLib|OvmfPkg/Library/BaseMemEncryptSevLib/SecMemEncryptSevLib.inf
CpuExceptionHandlerLib|UefiCpuPkg/Library/CpuExceptionHandlerLib/Xcode5SecPeiCpuExceptionHandlerLib.inf
CcProbeLib|OvmfPkg/Library/CcProbeLib/CcProbeLib.inf
VmgExitLib|OvmfPkg/Library/VmgExitLib/SecVmgExitLib.inf
PlatformHookLib|MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf
MemoryAllocationLib|MdePkg/Library/PeiMemoryAllocationLib/PeiMemoryAllocationLib.inf
HobLib|MdePkg/Library/PeiHobLib/PeiHobLib.inf

[Components]
OvmfPkg/Sec/SecMain.inf
OvmfPkg/ResetVector/ResetVector.inf


