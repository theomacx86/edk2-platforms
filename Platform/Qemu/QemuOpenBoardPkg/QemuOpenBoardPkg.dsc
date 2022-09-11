## @file
#  QemuOpenBoardPkg.dsc
#
#  Description file for QemuOpenBoardPkg
#
#  Copyright (c) 2022 Théo Jehl
#  SPDX-License-Identifier: BSD-2-Clause-Patent
##

[Defines]
  DSC_SPECIFICATION           = 0x0001001C
  PLATFORM_GUID               = 94797875-D562-40CF-8D55-ADD623C8D46C
  PLATFORM_NAME               = QemuOpenBoardPkg
  PLATFORM_VERSION            = 0.1
  SUPPORTED_ARCHITECTURES     = IA32 | X64
  FLASH_DEFINITION            = $(PLATFORM_NAME)/$(PLATFORM_NAME).fdf
  OUTPUT_DIRECTORY            = Build/$(PLATFORM_NAME)
  BUILD_TARGETS               = DEBUG | RELEASE | NOOPT
  SKUID_IDENTIFIER            = ALL
  SMM_REQUIRED                = FALSE
  !ifndef $(BOOT_STAGE)
    BOOT_STAGE                = 4
  !endif

!ifndef $(PEI_ARCH)
  !error "PEI_ARCH must be specified to build this feature!"
!endif
!ifndef $(DXE_ARCH)
  !error "DXE_ARCH must be specified to build this feature!"
!endif

[SkuIds]
  0 | DEFAULT

[Packages]
  MdePkg/MdePkg.dec
  MdeModulePkg/MdeModulePkg.dec
  MinPlatformPkg/MinPlatformPkg.dec
  QemuOpenBoardPkg/QemuOpenBoardPkg.dec
  UefiCpuPkg/UefiCpuPkg.dec
  OvmfPkg/OvmfPkg.dec


[PcdsFixedAtBuild]
  gMinPlatformPkgTokenSpaceGuid.PcdBootStage                            | $(BOOT_STAGE)

  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel                      | 0x802A00C7
  gEfiMdePkgTokenSpaceGuid.PcdFixedDebugPrintErrorLevel                 | 0x802A00C7
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask                         | 0x17

  # QEMU "memory" is functional even in SEC.  For simplicity, we just use that
  # "memory" for the temporary RAM
  gQemuOpenBoardPkgTokenSpaceGuid.PcdTemporaryRamBase                   | 0x1000000
  gQemuOpenBoardPkgTokenSpaceGuid.PcdTemporaryRamSize                   | 0x010000

  gQemuOpenBoardPkgTokenSpaceGuid.PcdDebugIoPort                        | 0x402
  gEfiMdePkgTokenSpaceGuid.PcdFSBClock                                  | 100000000

  # PCIe base address for Q35 machines
  # QEMU usable memory below 4G cannot exceed 2.8Gb
  gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress                     | 0xB0000000

  gEfiMdeModulePkgTokenSpaceGuid.PcdEmuVariableNvModeEnable             | TRUE
  gEfiMdeModulePkgTokenSpaceGuid.PcdResetOnMemoryTypeInformationChange  | FALSE

  gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspMBase                      | 0x00000000 # Will be updated by build

[PcdsFeatureFlag]
  gMinPlatformPkgTokenSpaceGuid.PcdSmiHandlerProfileEnable              | TRUE
  gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable                 | FALSE
  gMinPlatformPkgTokenSpaceGuid.PcdPerformanceEnable                    | FALSE
  gEfiMdeModulePkgTokenSpaceGuid.PcdDxeIplSupportUefiDecompress         | TRUE

  !if $(DXE_ARCH) == X64
    gEfiMdeModulePkgTokenSpaceGuid.PcdDxeIplSwitchToLongMode            | TRUE
  !else
    gEfiMdeModulePkgTokenSpaceGuid.PcdDxeIplSwitchToLongMode            | FALSE
  !endif


  !if gMinPlatformPkgTokenSpaceGuid.PcdBootStage == 1
    gMinPlatformPkgTokenSpaceGuid.PcdStopAfterDebugInit                 | TRUE
  !endif

  !if gMinPlatformPkgTokenSpaceGuid.PcdBootStage == 2
    gMinPlatformPkgTokenSpaceGuid.PcdStopAfterMemInit                   | TRUE
  !endif

  !if gMinPlatformPkgTokenSpaceGuid.PcdBootStage == 3
    gMinPlatformPkgTokenSpaceGuid.PcdBootToShellOnly                    | TRUE
  !endif

  !if gMinPlatformPkgTokenSpaceGuid.PcdBootStage == 5
    gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable               | TRUE
    gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable                         | TRUE
  !endif

  gMinPlatformPkgTokenSpaceGuid.PcdSerialTerminalEnable                 | TRUE
  gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable                           | FALSE

  !if $(SMM_REQUIRED) == TRUE
    gUefiOvmfPkgTokenSpaceGuid.PcdSmmSmramRequire                       | TRUE
    gUefiCpuPkgTokenSpaceGuid.PcdCpuHotPlugSupport                      | FALSE
    gEfiMdeModulePkgTokenSpaceGuid.PcdEnableVariableRuntimeCache        | FALSE
  !endif

[PcdsDynamicDefault]
  gUefiOvmfPkgTokenSpaceGuid.PcdOvmfHostBridgePciDevId                  | 0

  # Video setup
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution      | 640
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution        | 480

  gEfiMdeModulePkgTokenSpaceGuid.PcdSmbiosVersion                       | 0x0208
  gEfiMdeModulePkgTokenSpaceGuid.PcdSmbiosDocRev                        | 0x0

  gEfiMdePkgTokenSpaceGuid.PcdPlatformBootTimeOut                       | 3

  gUefiCpuPkgTokenSpaceGuid.PcdCpuMaxLogicalProcessorNumber             | 0
  gUefiCpuPkgTokenSpaceGuid.PcdCpuBootLogicalProcessorNumber            | 0

  !if $(SMM_REQUIRED) == TRUE
    gUefiOvmfPkgTokenSpaceGuid.PcdQ35TsegMbytes                         | 8
    gUefiOvmfPkgTokenSpaceGuid.PcdQ35SmramAtDefaultSmbase               | FALSE
    gUefiCpuPkgTokenSpaceGuid.PcdCpuSmmSyncMode                         | 0x01
    gUefiCpuPkgTokenSpaceGuid.PcdCpuSmmApSyncTimeout                    | 100000
  !endif

# Include Common libraries and then stage specific libraries and components
!include MinPlatformPkg/Include/Dsc/CoreCommonLib.dsc

!if gMinPlatformPkgTokenSpaceGuid.PcdBootStage >= 1
!include MinPlatformPkg/Include/Dsc/CorePeiLib.dsc
!include QemuOpenBoardPkg/Include/Dsc/Stage1.dsc.inc
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdBootStage >= 2
!include QemuOpenBoardPkg/Include/Dsc/Stage2.dsc.inc
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdBootStage >= 3
!include MinPlatformPkg/Include/Dsc/CoreDxeLib.dsc
!include QemuOpenBoardPkg/Include/Dsc/Stage3.dsc.inc
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdBootStage >= 4
!include QemuOpenBoardPkg/Include/Dsc/Stage4.dsc.inc
!endif

[LibraryClasses.Common]
  QemuOpenFwCfgLib        | QemuOpenBoardPkg/Library/QemuOpenFwCfgLib/QemuOpenFwCfgLib.inf
  PlatformHookLib         | MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf
  PlatformSecLib          | QemuOpenBoardPkg/Library/PlatformSecLib/PlatformSecLib.inf
  DebugLib                | MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
  PciCf8Lib               | MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf
  TimerLib                | OvmfPkg/Library/AcpiTimerLib/BaseAcpiTimerLib.inf
