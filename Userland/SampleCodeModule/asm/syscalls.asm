GLOBAL read
GLOBAL write
GLOBAL os_time
GLOBAL os_clear
GLOBAL os_draw
GLOBAL os_ticks
GLOBAL os_sec
GLOBAL os_beep
GLOBAL os_unbeep
GLOBAL os_requestMemorySpace
GLOBAL os_freeMemorySpace

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


os_ticks:
	start

	mov rdi, 0x01
	mov rsi, aux

	int 80h

	finish

os_sec:
	start

	mov rdi, 0x02
	mov rsi, aux

	int 80h

	finish

read:
	start

	; CAME AS: RDI --> file descriptor, RSI --> buffer, RDX --> bytes to read

	mov rcx, rdx
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, 0x03

	; CALL SYSCALL AS: RDI --> SysCode RSI --> file descriptor, RDX --> buffer, RCX --> bytes to read

	int 80h

	; In RAX returns the amount of bytes read and in the buffer are the characters read

	finish

write:
	start

	; CAME AS: RDI --> file descriptor, RSI --> buffer, RDX --> bytes to write

	mov rcx, rdx
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, 0x04

	; CALL SYSCALL AS: RDI --> SysCode RSI --> file descriptor, RDX --> buffer, RCX --> bytes to write

	int 80h

	; In RAX returns the amount of bytes written

	finish

os_time:
	start

	mov rdi, 0x05
	mov rsi, timeArray

	; CALL SYSCALL AS: RDI --> SysCode , RSI --> buffer to store time

	int 80h

	; In RAX returns the the string with the current time

	finish

os_clear:
	start

	mov rdi, 0x06

	int 80h

	finish


os_draw:
	start

	; CAME AS: RDI --> x , RSI --> y, RDX --> r, RCX --> g, R8 --> b

	mov r9, r8
	mov r8, rcx
	mov rcx, rdx
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, 0x07

	; CALL SYSCALL AS: RDI --> SysCode , RSI --> x, RDX --> y, RCX --> r, R8 --> g, R9 -->b

	int 80h

	finish

os_beep:
	start

	mov rdi, 0x08

	int 80h

	finish

os_unbeep:
	start

	mov rdi, 0x09

	int 80h

	finish

os_requestMemorySpace:
	start
	mov rsi, rdi
	mov rdi, 0x0A
	int 80h
	finish


os_freeMemorySpace:
	start
	mov rdx, rsi
	mov rsi,rdi
	mov rdi, 0x0B
	int 80h

	finish


section .data
	timeArray times 6 DW 0

section .bb
	aux resb 4	; para enteros
