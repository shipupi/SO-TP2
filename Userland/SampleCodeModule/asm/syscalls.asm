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
GLOBAL os_schedule
GLOBAL os_addProcess
GLOBAL os_endProcess
GLOBAL os_listProcesses
GLOBAL os_sleep
GLOBAL os_sleep_seconds
GLOBAL os_ipc_create
GLOBAL os_ipc_write
GLOBAL os_ipc_read
GLOBAL os_sleepPID
GLOBAL os_wakePID
GLOBAL os_ipc_list
GLOBAL os_ipc_close
GLOBAL os_mut_create
GLOBAL os_mut_request
GLOBAL os_mut_release
GLOBAL os_mut_delete
GLOBAL os_mut_list
GLOBAL os_pid
GLOBAL os_pstat
GLOBAL os_split_screen
GLOBAL os_unsplit_screen

GLOBAL os_pipe_create
GLOBAL os_pipe_delete
GLOBAL os_pipe_read
GLOBAL os_pipe_write
GLOBAL die

GLOBAL os_change_priority
GLOBAL os_kill

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

os_schedule:
	start
	mov rdi, 0x0C
	int 80h
	finish

os_addProcess:
	start
	mov r10, r9
	mov r9, r8
	mov r8, rcx
	mov rcx,rdx
	mov rdx,rsi
	mov rsi,rdi
	mov rdi, 0x0D
	int 80h
	finish

os_endProcess:
	start
	mov rsi, rdi
	mov rdi, 0x0E
	int 80h
	finish

os_listProcesses:
	start
	mov rdi, 0x0F
	int 80h
	finish

os_sleep:
	start
	mov rdi, 0x10
	int 80h
	finish

os_ipc_create:
	start
	mov rdx,rsi
	mov rsi,rdi
	mov rdi, 0x11
	int 80h
	finish

os_ipc_read:
	start
	mov rcx,rdx
	mov rdx,rsi
	mov rsi,rdi
	mov rdi, 0x12
	int 80h
	finish

os_ipc_write:
	start
	mov rcx,rdx
	mov rdx,rsi
	mov rsi,rdi
	mov rdi, 0x13
	int 80h
	finish

os_sleepPID:
	start
	mov rsi,rdi
	mov rdi, 0x14
	int 80h
	finish

os_wakePID:
	start
	mov rsi,rdi
	mov rdi, 0x15
	int 80h
	finish

os_ipc_list:
	start
	mov rdi, 0x16
	int 80h
	finish

os_ipc_close:
	start
	mov rsi,rdi
	mov rdi,0x17
	int 80h
	finish

os_mut_create:
	start
	mov rsi, rdi
	mov rdi, 0x18
	int 80h
	finish

os_mut_request:
	start
	mov rsi, rdi
	mov rdi, 0x19
	int 80h
	finish

os_mut_release:
	start
	mov rsi, rdi
	mov rdi, 0x1A
	int 80h
	finish

os_mut_delete:
	start
	mov rsi, rdi
	mov rdi, 0x1B
	int 80h
	finish

os_mut_list:
	start
	mov rdi, 0x1C
	int 80h
	finish

os_pid:
	start
	mov rdi, 0x1D
	int 80h
	finish

os_pstat:
	start
	mov rsi,rdi
	mov rdi, 0x1E
	int 80h
	finish

os_pipe_create:
	start

	mov rsi,rdi
	mov rdi, 0x1F
	int 80h
	finish

os_pipe_delete:
	start
	mov rsi,rdi
	mov rdi, 0x20
	int 80h
	finish

os_pipe_read:
	start
	mov rcx,rdx
	mov rdx,rsi
	mov rsi,rdi
	mov rdi, 0x21
	int 80h
	finish

os_pipe_write:
	start
	mov rcx,rdx
	mov rdx,rsi
	mov rsi,rdi
	mov rdi, 0x22
	int 80h
	finish

os_change_priority:
	start
	mov rdx,rsi
	mov rsi,rdi
	mov rdi, 0x23
	int 80h
	finish

os_split_screen:
	start
	mov rdi, 0x24
	int 80h
	finish
os_unsplit_screen:
	start
	mov rdi, 0x25
	int 80h
	finish

os_sleep_seconds:
	start
	mov rsi, rdi
	mov rdi, 0x26
	int 80h
	finish
	
os_kill:
	start
	mov rsi, rdi
	mov rdi, 0x27
	int 80h
	finish

section .data
	timeArray times 6 DW 0

section .bb
	aux resb 4	; para enteros


die:
	cli
	hlt
	ret