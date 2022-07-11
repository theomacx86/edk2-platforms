ARCH?=IA32
ifeq ($(WORKSPACE),)
	$(error "WORKSPACE is not defined, run edksetup.sh")
endif
TARGET?=DEBUG
TOOLCHAIN?=GCC5

Qemu:
	build -a $(ARCH) -p Platform/Qemu/QemuOpenBoardPkg/QemuOpenBoardPkg.dsc

QemuRunDebug:
	rm -f $(WORKSPACE)/debug.log
	build -a $(ARCH) -p Platform/Qemu/QemuOpenBoardPkg/QemuOpenBoardPkg.dsc -y Report.txt
	qemu-system-x86_64 -bios $(WORKSPACE)/Build/QemuOpenBoardPkg/$(TARGET)_$(TOOLCHAIN)/FV/QEMUOPENBOARDPKG.fd -debugcon file:$(WORKSPACE)/debug.log -global isa-debugcon.iobase=0x402 -serial stdio -s -S

QemuRun:
	rm -f $(WORKSPACE)/debug.log
	build -a $(ARCH) -p Platform/Qemu/QemuOpenBoardPkg/QemuOpenBoardPkg.dsc -y Report.txt
	qemu-system-x86_64 -bios $(WORKSPACE)/Build/QemuOpenBoardPkg/$(TARGET)_$(TOOLCHAIN)/FV/QEMUOPENBOARDPKG.fd -debugcon file:$(WORKSPACE)/debug.log -global isa-debugcon.iobase=0x402 -serial stdio

clean:
	rm -f $(WORKSPACE)/debug.log
	rm -f $(WORKSPACE)/Report.txt
	rm -rf $(WORKSPACE)/Build