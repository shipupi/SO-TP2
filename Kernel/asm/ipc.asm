GLOBAL ipc_sleep

section .text

%macro start 0
	push rbp
	mov rbp, rsp

	push rbx
	push rcx
	push r12
	push r13
	push r15
%endmacro

%macro finish 0
	pop r15
	pop r13
	pop r12
	pop rcx
	pop rbx

	mov rsp, rbp
	pop rbp
	ret
%endmacro


ipc_sleep:
	start
	mov rdi, 0x10
	int 80h
	finish