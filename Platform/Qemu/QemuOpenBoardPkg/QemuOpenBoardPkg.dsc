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

[Packages]
  MdePkg/MdePkg.dec
  MinPlatformPkg/MinPlatformPkg.dec
  QemuOpenBoardPkg/QemuOpenBoardPkg.dec

[PcdsFixedAtBuild]
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel   | 0x802A00C7
  gEfiMdePkgTokenSpaceGuid.PcdFixedDebugPrintErrorLevel   | 0x802A00C7
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask           | 0x27

  gUefiQemuOpenBoardPkgTokenSpaceGuid.PcdDebugIoPort|0x402
  # Worth investigating: 0x010000 doesn't work as a temporary ram base once
  # I fixed the stack. It should be firmly within lower memory (640KiB). 
  gUefiQemuOpenBoardPkgTokenSpaceGuid.PcdTemporaryRamBase|0x100000
  gUefiQemuOpenBoardPkgTokenSpaceGuid.PcdTemporaryRamSize|0x010000


[PcdsFeatureFlag]
  gMinPlatformPkgTokenSpaceGuid.PcdSmiHandlerProfileEnable|TRUE
  gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable | FALSE
  gMinPlatformPkgTokenSpaceGuid.PcdPerformanceEnable | FALSE


################################################################################
#
# Library classes
#
################################################################################

!include MinPlatformPkg/Include/Dsc/CoreCommonLib.dsc
!include MinPlatformPkg/Include/Dsc/CorePeiLib.dsc
!include MinPlatformPkg/Include/Dsc/CoreDxeLib.dsc

!include QemuOpenBoardPkg/Include/Dsc/Stage1.dsc.inc


[LibraryClasses.common]
QemuFwCfgLib|QemuOpenBoardPkg/Library/QemuFwCfgLib/QemuFwCfgLib.inf
PlatformHookLib|MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf
PlatformSecLib|QemuOpenBoardPkg/Library/PlatformSecLib/PlatformSecLib.inf
DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
PciCf8Lib|MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf

# Investigate: PlatformDebugLibIoPort doesn't work for non-SEC/PEI_CORE
# [LibraryClasses.common.SEC]
# DebugLib|OvmfPkg/Library/PlatformDebugLibIoPort/PlatformRomDebugLibIoPort.inf

[Components]
QemuOpenBoardPkg/Library/PlatformInitPei/PlatformInitPei.inf

#stage 2
MinPlatformPkg/PlatformInit/SiliconPolicyPei/SiliconPolicyPeiPostMem.inf
MinPlatformPkg/PlatformInit/PlatformInitPei/PlatformInitPostMem.inf
MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf
#MdeModulePkg/Universal/ResetSystemRuntimeDxe/ResetSystemRuntimeDxe.inf
#MdeModulePkg/Bus/Pci/PciHostBridgeDxe/PciHostBridgeDxe.inf
