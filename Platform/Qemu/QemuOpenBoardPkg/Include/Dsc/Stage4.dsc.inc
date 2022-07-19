[Components]
OvmfPkg/AcpiPlatformDxe/AcpiPlatformDxe.inf
MdeModulePkg/Universal/Acpi/AcpiTableDxe/AcpiTableDxe.inf

OvmfPkg/SataControllerDxe/SataControllerDxe.inf
MdeModulePkg/Bus/Ata/AtaAtapiPassThru/AtaAtapiPassThru.inf
MdeModulePkg/Bus/Ata/AtaBusDxe/AtaBusDxe.inf
MdeModulePkg/Bus/Pci/UhciDxe/UhciDxe.inf
MdeModulePkg/Bus/Pci/EhciDxe/EhciDxe.inf
MdeModulePkg/Bus/Pci/XhciDxe/XhciDxe.inf
MdeModulePkg/Bus/Usb/UsbBusDxe/UsbBusDxe.inf
MdeModulePkg/Bus/Usb/UsbKbDxe/UsbKbDxe.inf

!if SMM_ENABLED == TRUE
    MdeModulePkg/Core/PiSmmCore/PiSmmIpl.inf
    MdeModulePkg/Core/PiSmmCore/PiSmmCore.inf
    MdeModulePkg/Universal/ReportStatusCodeRouter/Smm/ReportStatusCodeRouterSmm.inf
    MdeModulePkg/Universal/StatusCodeHandler/Smm/StatusCodeHandlerSmm.inf
    UefiCpuPkg/PiSmmCpuDxeSmm/PiSmmCpuDxeSmm.inf
    UefiCpuPkg/CpuIo2Smm/CpuIo2Smm.inf
    MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteSmm.inf
    IntelSiliconPkg/Feature/Flash/SpiFvbService/SpiFvbServiceSmm.inf
!endif

