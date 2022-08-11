[LibraryClasses.common]
    ResetSystemLib|QemuOpenBoardPkg/Library/ResetSystemLib/ResetSystemLib.inf
    PciHostBridgeLib|OvmfPkg/Library/PciHostBridgeLib/PciHostBridgeLib.inf
    PciHostBridgeUtilityLib|OvmfPkg/Library/PciHostBridgeUtilityLib/PciHostBridgeUtilityLib.inf
    DxeHardwareInfoLib|OvmfPkg/Library/HardwareInfoLib/DxeHardwareInfoLib.inf

[LibraryClasses.common.DXE_DRIVER, LibraryClasses.common.DXE_RUNTIME_DRIVER, LibraryClasses.common.DXE_SMM_DRIVER, LibraryClasses.common.UEFI_DRIVER, LibraryClasses.common.UEFI_APPLICATION, LibraryClasses.common.SMM_CORE]
    PciLib|OvmfPkg/Library/DxePciLibI440FxQ35/DxePciLibI440FxQ35.inf

[Components.IA32]
    UefiCpuPkg/CpuMpPei/CpuMpPei.inf{
        <LibraryClasses>
        MpInitLib|UefiCpuPkg/Library/MpInitLib/PeiMpInitLib.inf
        TimerLib|OvmfPkg/Library/AcpiTimerLib/BaseAcpiTimerLib.inf
    }
    MinPlatformPkg/PlatformInit/SiliconPolicyPei/SiliconPolicyPeiPostMem.inf
    MinPlatformPkg/PlatformInit/PlatformInitPei/PlatformInitPostMem.inf
    MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf

    [Components.X64]
    MdeModulePkg/Universal/ResetSystemRuntimeDxe/ResetSystemRuntimeDxe.inf
    MdeModulePkg/Bus/Pci/PciHostBridgeDxe/PciHostBridgeDxe.inf