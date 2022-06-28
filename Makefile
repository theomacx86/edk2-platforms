Qemu:
	build -a $(ARCH) -p Platform/Qemu/QemuOpenBoardPkg/QemuOpenBoardPkg.dsc

QemuRunDebug:
	rm $(WORKSPACE)/debug.log
	build -a $(ARCH) -p Platform/Qemu/QemuOpenBoardPkg/QemuOpenBoardPkg.dsc
	qemu-system-x86_64 -bios $(WORKSPACE)/Build/QemuOpenBoardPkg/$(TARGET)_$(TOOLCHAIN)/FV/QEMUOPENBOARDPKG.fd -debugcon file:$(WORKSPACE)/debug.log -global isa-debugcon.iobase=0x402 -monitor stdio -s -S

QemuRun:
	rm $(WORKSPACE)/debug.log
	build -a $(ARCH) -p Platform/Qemu/QemuOpenBoardPkg/QemuOpenBoardPkg.dsc
	qemu-system-x86_64 -bios $(WORKSPACE)/Build/QemuOpenBoardPkg/$(TARGET)_$(TOOLCHAIN)/FV/QEMUOPENBOARDPKG.fd -debugcon file:$(WORKSPACE)/debug.log -global isa-debugcon.iobase=0x402 -monitor stdio 