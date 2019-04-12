GLOBAL getTime

section .text

getTime:
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	push r13
	push r15
	cli   				; deshabilita interrupciones enmascarables

	xor rax, rax
	mov al, 0x8B			; select status register B, and disable NMI

	out 70h, al
	in al, 71h
	or al, 0x04			; poneme en uno este bit (Setting up the binary date/time, BCD is the default)
	out 71h, al			; piso la configuracion vieja para tener la que cambie
	xor rax, rax

	mov rax, rdi		
	movzx rax, al			; con in out se opera con 1 byte
	out 70h, al			; le digo que quiero
	in al, 71h			; me lo pone en al
	movzx rax, al
	sti 				; enable enmaskarable interrupts


	pop r15
	pop r13
	pop r12
	pop rbx
	mov rsp, rbp
	pop rbp
	ret

;le seteo la configuracion que quiero 


