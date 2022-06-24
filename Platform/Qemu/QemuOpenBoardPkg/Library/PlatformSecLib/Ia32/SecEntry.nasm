CODE_SEG equ code_segment_descriptor - GDT_START
DATA_SEG equ data_segment_descriptor - GDT_START

extern ASM_PFX(SecStartup)

BITS 16
align 4
global ASM_PFX(_ModuleEntryPoint)
ASM_PFX(_ModuleEntryPoint):
    cli 
    ; lgdt[GDT_Descriptor]
    mov esi, GDT_Descriptor
    db 66h
    lgdt[cs:si]

    mov     eax, cr0                 
    or      eax, 1            
    mov     cr0, eax                   
               
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    mov esi, ProtectedModeEntryLinearAddress
    
    jmp dword far [cs:si]



BITS 32
align 4
protected_mode:
    PROTECTED_MODE equ $
    mov esp, 0x1000 ; Placeholder, allocate 4Kb of RAM
    mov eax, esp
    push eax
    add eax, -4
    push eax
    ; boot firmware volume?
    call ASM_PFX(SecStartup)



align 8
NULL_SEGMENT    equ $ - GDT_START
GDT_START:
    
    ; null descriptor
    dd 0x0
    dd 0x0

    CODE_SEL        equ $ - GDT_START
    code_segment_descriptor:
    dw 0xFFFF ; Limit 15 : 0
    dw 0x0      ; Base 15 : 0

    db 0x0      ; Base 16 : 23

               ; Present : 1 - DPL (Segment) : 00 - S (Descriptor byte): 1 -- 1001
               ; Executable : 1 - DC : 0 - RW : 1 - A: 0
               ; 1001 1010 - 
    db 0x9B

    db 0xCF 

    db 0x0
    
    DATA_SEL        equ $ - GDT_START
    data_segment_descriptor:
    dw 0xFFFF ; Limit 15 : 0
    dw 0x0      ; Base 15 : 0

    db 0x0      ; Base 16 : 23

               ; Present : 1 - DPL (Segment) : 00 - S (Descriptor byte): 1 -- 1001
               ; Executable : 0 - DC : 0 - RW : 1 - A: 0
               ; 1001 0010 - 
    db 0x93

    db 0xCF

    db 0x0
    
GDT_END:

GDT_Descriptor:
    dw GDT_END - GDT_START - 1 
    dd GDT_START

ProtectedModeEntryLinearAddress:
ProtectedModeEntryLinear:
  DD      protected_mode  ; Offset of our 32 bit code
  DW      CODE_SEL

