global _start
extern long_mode_start

section .multiboot_header
header_start:
	dd 0xe85250d6 
	dd 0
	dd header_end - header_start
	dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))
	dw 0
	dw 0
	dd 8
header_end:

section .text
[BITS 32]
_start:
	mov esp, stack_top
	call check_CPUID
	call check_Long_Mode
	call setup_page_tables
	call enable_paging
	lgdt [gdt64.pointer]
	jmp gdt64.code:long_mode_start
	hlt

check_CPUID:
	pushfd
	pop eax
	mov ecx, eax
	xor eax, 1 << 21
	push eax
	popfd
	pushfd
	pop eax
	push ecx
	popfd
	xor eax, ecx
	jz .NoCPUID
	ret
.NoCPUID:
	mov al, "C"
	jmp error

check_Long_Mode:
	mov eax, 0x80000000    
	cpuid                  
	cmp eax, 0x80000001    
	jb .NoLongMode

	mov eax, 0x80000001    
    cpuid                  
    test edx, 1 << 29      
    jz .NoLongMode 
	ret
.NoLongMode:
	mov al, "C"
	jmp error

error:
	mov dword [0xb8000], 0x4f524f45
	mov dword [0xb8004], 0x4f3a4f52
	mov dword [0xb8008], 0x4f204f20
	mov byte  [0xb800a], al
	hlt
setup_page_tables:
	mov eax, p3_table
	or eax, 0b11 
	mov [p4_table], eax
	
	mov eax, p2_table
	or eax, 0b11 
	mov [p3_table], eax

	mov ecx, 0 
.loop:

	mov eax, 0x200000 
	mul ecx
	or eax, 0b10000011 
	mov [p2_table + ecx * 8], eax

	inc ecx 
	cmp ecx, 512 
	jne .loop 

	ret

enable_paging:
	
	mov eax, p4_table
	mov cr3, eax
	
	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr
	
	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax

	ret

section .bss
align 4096
p4_table:
    resb 4096
p3_table:
    resb 4096
p2_table:
    resb 4096
stack_bottom:
	resb 4096 * 4
stack_top:

section .rodata
gdt64:
	dq 0 
.code: equ $ - gdt64
	dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) 
.data: equ $ - gdt64
    dq (1<<44) | (1<<47) | (1<<41)
.pointer:
	dw $ - gdt64 - 1  
	dq gdt64 
