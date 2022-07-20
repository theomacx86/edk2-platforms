TARGET?=DEBUG
TOOLCHAIN?=GCC5

Qemu:
	build -a X64 -a IA32 -p Platform/Qemu/QemuOpenBoardPkg/QemuOpenBoardPkg.dsc -y Report.txt

QemuRunDebug:
	rm -f $(WORKSPACE)/debug.log
	build -a X64 -a IA32 -p Platform/Qemu/QemuOpenBoardPkg/QemuOpenBoardPkg.dsc -y Report.txt
	qemu-system-x86_64 -bios $(WORKSPACE)/Build/QemuOpenBoardPkg/$(TARGET)_$(TOOLCHAIN)/FV/QEMUOPENBOARDPKG.fd -debugcon file:$(WORKSPACE)/debug.log -global isa-debugcon.iobase=0x402 -s -S  -serial stdio -d int

QemuRun:
	rm -f $(WORKSPACE)/debug.log
	build -a X64 -a IA32 -p Platform/Qemu/QemuOpenBoardPkg/QemuOpenBoardPkg.dsc -y Report.txt
	qemu-system-x86_64 -bios $(WORKSPACE)/Build/QemuOpenBoardPkg/$(TARGET)_$(TOOLCHAIN)/FV/QEMUOPENBOARDPKG.fd -debugcon file:$(WORKSPACE)/debug.log -global isa-debugcon.iobase=0x402 -serial stdio -smp 1 

QemuRunQ35:
	rm -f $(WORKSPACE)/debug.log
	build -a X64 -a IA32 -p Platform/Qemu/QemuOpenBoardPkg/QemuOpenBoardPkg.dsc -y Report.txt
	qemu-system-x86_64 -machine q35 -bios $(WORKSPACE)/Build/QemuOpenBoardPkg/$(TARGET)_$(TOOLCHAIN)/FV/QEMUOPENBOARDPKG.fd -debugcon file:$(WORKSPACE)/debug.log -global isa-debugcon.iobase=0x402 -serial stdio


clean:
	rm -f $(WORKSPACE)/debug.log
	rm -f $(WORKSPACE)/Report.txt
	rm -rf $(WORKSPACE)/Build