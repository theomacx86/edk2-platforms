[Defines]
    DSC_SPECIFICATION           = 0x0001001C
    PLATFORM_GUID               = 94797875-D562-40CF-8D55-ADD623C8D46C
    PLATFORM_NAME               = QemuOpenBoardPkg
    PLATFORM_VERSION            = 0.1
    SUPPORTED_ARCHITECTURES     = IA32|X64
    FLASH_DEFINITION            = $(PLATFORM_NAME)/$(PLATFORM_NAME).fdf
    OUTPUT_DIRECTORY            = Build/$(PLATFORM_NAME)
    BUILD_TARGETS               = DEBUG|RELEASE
    SKUID_IDENTIFIER            = ALL
    SMM_ENABLED                 = FALSE

[SkuIds]
  0|DEFAULT

[Packages]
  MdePkg/MdePkg.dec
  MdeModulePkg/MdeModulePkg.dec
  MinPlatformPkg/MinPlatformPkg.dec
  QemuOpenBoardPkg/QemuOpenBoardPkg.dec
  UefiCpuPkg/UefiCpuPkg.dec

[PcdsFixedAtBuild]
  gMinPlatformPkgTokenSpaceGuid.PcdBootStage|4
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel   | 0x802A00C7
  gEfiMdePkgTokenSpaceGuid.PcdFixedDebugPrintErrorLevel   | 0x802A00C7
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask           | 0x17

  gUefiQemuOpenBoardPkgTokenSpaceGuid.PcdDebugIoPort|0x402
  # Worth investigating: 0x010000 doesn't work as a temporary ram base once
  # I fixed the stack. It should be firmly within lower memory (640KiB). 
  gUefiQemuOpenBoardPkgTokenSpaceGuid.PcdTemporaryRamBase|0x1000000
  gUefiQemuOpenBoardPkgTokenSpaceGuid.PcdTemporaryRamSize|0x010000

  gEfiMdeModulePkgTokenSpaceGuid.PcdEmuVariableNvModeEnable|TRUE
  gEfiMdePkgTokenSpaceGuid.PcdFSBClock|100000000

  gEfiMdeModulePkgTokenSpaceGuid.PcdResetOnMemoryTypeInformationChange|FALSE
  gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress|0xB0000000

[PcdsFeatureFlag]
  gMinPlatformPkgTokenSpaceGuid.PcdSmiHandlerProfileEnable|TRUE
  gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable | FALSE
  gMinPlatformPkgTokenSpaceGuid.PcdPerformanceEnable | FALSE
  gEfiMdeModulePkgTokenSpaceGuid.PcdDxeIplSwitchToLongMode | TRUE
  gMinPlatformPkgTokenSpaceGuid.PcdBootToShellOnly|TRUE
  gMinPlatformPkgTokenSpaceGuid.PcdSerialTerminalEnable|TRUE
  gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable|FALSE

[PcdsDynamicDefault]
  gUefiOvmfPkgTokenSpaceGuid.PcdOvmfHostBridgePciDevId|0

  #video setup
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|640
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|480

  gEfiMdeModulePkgTokenSpaceGuid.PcdSmbiosVersion|0x0208
  gEfiMdeModulePkgTokenSpaceGuid.PcdSmbiosDocRev|0x0

  gEfiMdePkgTokenSpaceGuid.PcdPlatformBootTimeOut|3


################################################################################
#
# Library classes
#
################################################################################

!include MinPlatformPkg/Include/Dsc/CoreCommonLib.dsc
!include MinPlatformPkg/Include/Dsc/CorePeiLib.dsc
!include MinPlatformPkg/Include/Dsc/CoreDxeLib.dsc
!include QemuOpenBoardPkg/Include/Dsc/Stage1.dsc.inc
!include QemuOpenBoardPkg/Include/Dsc/Stage2.dsc.inc
!include QemuOpenBoardPkg/Include/Dsc/Stage3.dsc.inc
!include QemuOpenBoardPkg/Include/Dsc/Stage4.dsc.inc


[LibraryClasses.common]
QemuFwCfgLib|QemuOpenBoardPkg/Library/OpenQemuFwCfgLib/OpenQemuFwCfgLib.inf
PlatformHookLib|MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf
PlatformSecLib|QemuOpenBoardPkg/Library/PlatformSecLib/PlatformSecLib.inf
DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
PciCf8Lib|MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf
TimerLib|OvmfPkg/Library/AcpiTimerLib/BaseAcpiTimerLib.inf


[LibraryClasses.common.DXE_CORE]
TimerLib|OvmfPkg/Library/AcpiTimerLib/BaseAcpiTimerLib.inf

[LibraryClasses.common.DXE_DRIVER, LibraryClasses.common.DXE_RUNTIME_DRIVER, LibraryClasses.common.DXE_SMM_DRIVER, LibraryClasses.common.UEFI_DRIVER, LibraryClasses.common.UEFI_APPLICATION, LibraryClasses.common.SMM_CORE]
TimerLib|OvmfPkg/Library/AcpiTimerLib/DxeAcpiTimerLib.inf
QemuFwCfgLib|OvmfPkg/Library/QemuFwCfgLib/QemuFwCfgDxeLib.inf
MemEncryptSevLib|OvmfPkg/Library/BaseMemEncryptSevLib/DxeMemEncryptSevLib.inf
MemEncryptTdxLib|OvmfPkg/Library/BaseMemEncryptTdxLib/BaseMemEncryptTdxLibNull.inf
Tcg2PhysicalPresenceLib|OvmfPkg/Library/Tcg2PhysicalPresenceLibNull/DxeTcg2PhysicalPresenceLib.inf
ResetSystemLib|OvmfPkg/Library/ResetSystemLib/DxeResetSystemLib.inf
PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
[LibraryClasses.common.SEC]
DebugLib|OvmfPkg/Library/PlatformDebugLibIoPort/PlatformRomDebugLibIoPort.inf

[Components.X64]
  MdeModulePkg/Bus/Scsi/ScsiBusDxe/ScsiBusDxe.inf
  MdeModulePkg/Bus/Scsi/ScsiDiskDxe/ScsiDiskDxe.inf
  OvmfPkg/SataControllerDxe/SataControllerDxe.inf
  MdeModulePkg/Bus/Ata/AtaAtapiPassThru/AtaAtapiPassThru.inf
  MdeModulePkg/Bus/Ata/AtaBusDxe/AtaBusDxe.inf
  MdeModulePkg/Bus/Pci/NvmExpressDxe/NvmExpressDxe.inf
  MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
  MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
