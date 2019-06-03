  
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL timer_tick
GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _syscall

GLOBAL _exception0Handler
GLOBAL _exception6Handler

EXTERN irqDispatcher
EXTERN sys_read
EXTERN sys_write
EXTERN sys_time
EXTERN sys_pixel
EXTERN sys_clear
EXTERN sys_beep
EXTERN sys_unbeep
EXTERN sys_ticks
EXTERN sys_sec
EXTERN sys_requestMemorySpace
EXTERN sys_freeMemorySpace
EXTERN sys_schedule
EXTERN sys_addProcess
EXTERN sys_endProcess
EXTERN sys_listProcesses
EXTERN sys_sleep_seconds
EXTERN sys_ipc_create
EXTERN sys_ipc_write
EXTERN sys_ipc_read
EXTERN sys_sleepPID
EXTERN sys_wakePID
EXTERN sys_ipc_list
EXTERN sys_ipc_close
EXTERN sys_halt

EXTERN sys_mut_create
EXTERN sys_mut_request
EXTERN sys_mut_release
EXTERN sys_mut_delete
EXTERN sys_mut_list
EXTERN sys_pid
EXTERN sys_pstat
EXTERN sys_split_screen
EXTERN sys_unsplit_screen
EXTERN printInt

EXTERN printf
EXTERN registerValueToString
EXTERN printUint
EXTERN nextLine
EXTERN reboot
EXTERN schedule
EXTERN sleep
EXTERN timer_handler

EXTERN sys_pipe_create
EXTERN sys_pipe_delete
EXTERN sys_pipe_read
EXTERN sys_pipe_write

EXTERN sys_change_priority

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
  push fs
  push gs
%endmacro

%macro popState 0
  pop gs
  pop fs
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al
	popState
	iretq
%endmacro



_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push rbp
    mov rbp, rsp
    mov ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
  ; Partes sacadas de rowdaboat
  ; Context Switch
  pushState
  call timer_handler
  ; mov rdi, rsp ; Load the parameters (current RSP) for the scheduler
  ; call printInt
  ; mov rdi, 1
  ; call nextLine
  mov rdi, rsp
  call schedule  
  mov rsp, rax  ;PUT the pointer given by schedule in the stack pointer
  mov al, 20h ; Send end of interrupt
  out 20h, al
  popState
  iretq
  ; End of context switch




;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

_syscall:

	cmp rdi, 0x01     ; syscall de total ticks
	je .syscall01

 	cmp rdi, 0x02     ; syscall de ticks per sec
  	je .syscall02

	cmp rdi, 0x03 		; syscall del read
	je .syscall03

	cmp rdi, 0x04		; syscall de write
	je .syscall04

	cmp rdi, 0x05		; syscall de time
	je .syscall05
	
	cmp rdi, 0x06		; syscall de clear
	je .syscall06

	cmp rdi, 0x07		; syscall de pixel
	je .syscall07

	cmp rdi, 0x08		; syscall de beep
	je .syscall08
	
	cmp rdi, 0x09		; syscall de unbeep
	je .syscall09

  cmp rdi, 0x0A   ; syscall de requestmemoryspace
  je .syscall0A

  cmp rdi, 0x0B   ; syscall de freeMemorySpace
  je .syscall0B

  cmp rdi, 0x0C   ; syscall de schedule
  je .syscall0C

  cmp rdi, 0x0D   ; syscall de addProcess
  je .syscall0D

  cmp rdi, 0x0E   ; syscall de endProcess
  je .syscall0E

  cmp rdi, 0x0F   ; syscall de listProcesses
  je .syscall0F

  cmp rdi, 0x10   ; syscall del sleep
  je .syscall10

  cmp rdi, 0x11   ; syscall de create
  je .syscall11

  cmp rdi, 0x12   ; syscall de write
  je .syscall12

  cmp rdi, 0x13   ; syscall de read
  je .syscall13

  cmp rdi, 0x14   ; syscall de sleepPID
  je .syscall14

  cmp rdi, 0x15   ; syscall de sleepPID
  je .syscall15

  cmp rdi, 0x16   ; syscall de ipc_list
  je .syscall16

  cmp rdi, 0x17   ; syscall de ipc_close
  je .syscall17

  cmp rdi, 0x18   ; mut_create
  je .syscall18

  cmp rdi, 0x19   ; mut_request
  je .syscall19

  cmp rdi, 0x1A   ; mut_release
  je .syscall1A

  cmp rdi, 0x1B   ; mut_delete
  je .syscall1B

  cmp rdi, 0x1C   ; mut_list
  je .syscall1C

  cmp rdi, 0x1D   ; pid
  je .syscall1D

  cmp rdi, 0x1E   ; pstat
  je .syscall1E

  cmp rdi, 0x1F   ; create pipe
  je .syscall1F

  cmp rdi, 0x20   ; delete pipe
  je .syscall20

  cmp rdi, 0x21   ; pipe read
  je .syscall21

  cmp rdi, 0x22   ; pipe write
  je .syscall22

  cmp rdi, 0x23   ; change priority
  je .syscall23

  cmp rdi, 0x24   ; split screen
  je .syscall24

  cmp rdi, 0x25   ; unsplit screen
  je .syscall25

  cmp rdi, 0x26   ; sleep_seconds
  je .syscall26

.continue:
	iretq	;Dont use ret when returning from int call


.syscall01:
  mov rdi, rsi  ; re-ordering the arguments to send to sys_ticks
  call sys_ticks
  jmp .continue

.syscall02:
  mov rdi, rsi  ; re-ordering the arguments to send to sys_ticks_per_sec
  call sys_sec
  jmp .continue

.syscall03:
	mov rdi, rsi 	; re-ordering the arguments to send to sys_read
	mov rsi, rdx
	mov rdx, rcx
	call sys_read
	jmp .continue

.syscall04:
	mov rdi, rsi 	; re-ordering the arguments to send to sys_write
	mov rsi, rdx
	mov rdx, rcx
	call sys_write
	jmp .continue

.syscall05:
	mov rdi, rsi 	; re-ordering the arguments to send to sys_time
	call sys_time
	jmp .continue

.syscall06:
	call sys_clear
	jmp .continue

.syscall07:
	mov rdi, rsi	; re-ordering the arguments to send to sys_pixel
	mov rsi, rdx
	mov rdx, rcx
	mov rcx, r8
	mov r8, r9
	call sys_pixel
	jmp .continue

.syscall08:
	call sys_beep
	jmp .continue

.syscall09:
	call sys_unbeep
	jmp .continue


.syscall0A:
  mov rdi, rsi
  call sys_requestMemorySpace
  jmp .continue

.syscall0B:

  mov rdi, rsi
  mov rsi, rdx 
  call sys_freeMemorySpace
  jmp .continue

.syscall0C:
  call sys_schedule
  jmp .continue

.syscall0D:
  mov rdi, rsi
  mov rsi, rdx
  mov rdx, rcx
  mov rcx, r8
  mov r8 , r9
  mov r9 , r10
  call sys_addProcess
  jmp .continue

.syscall0E:
  mov rdi, rsi
  call sys_endProcess
  jmp .continue

.syscall0F:
  call sys_listProcesses
  jmp .continue

.syscall10:  
  pushState
  call sleep
  mov rdi, rsp ; Load the parameters (current RSP) for the scheduler
  call schedule  
  mov rsp, rax  ;PUT the pointer given by schedule in the stack pointer
  popState
  iretq
.syscall11:
  mov rdi, rsi
  mov rsi, rdx
  call sys_ipc_create
  jmp .continue

.syscall12:
  mov rdi, rsi
  mov rsi, rdx
  mov rdx, rcx
  call sys_ipc_read
  jmp .continue

.syscall13:
  mov rdi, rsi
  mov rsi, rdx
  mov rdx, rcx
  call sys_ipc_write
  jmp .continue

.syscall14:
  mov rdi, rsi
  call sys_sleepPID
  jmp .continue

.syscall15:
  mov rdi, rsi
  call sys_wakePID
  jmp .continue

.syscall16:
  call sys_ipc_list
  jmp .continue

.syscall17:
  mov rdi, rsi
  call sys_ipc_close
  jmp .continue

.syscall18:
  mov rdi, rsi
  call sys_mut_create
  jmp .continue

.syscall19:
  mov rdi, rsi
  call sys_mut_request
  jmp .continue

.syscall1A:
  mov rdi, rsi
  call sys_mut_release
  jmp .continue

.syscall1B:
  mov rdi, rsi
  call sys_mut_delete
  jmp .continue

.syscall1C:
  call sys_mut_list
  jmp .continue

.syscall1D:
  call sys_pid
  jmp .continue

.syscall1E:
  mov rdi, rsi
  call sys_pstat
  jmp .continue

  .syscall1F:
  mov rdi, rsi
  call sys_pipe_create
  jmp .continue

  .syscall20:
  mov rdi, rsi
  call sys_pipe_delete
  jmp .continue

  .syscall21:
  mov rdi, rsi
  mov rsi, rdx
  mov rdx, rcx
  call sys_pipe_read
  jmp .continue

  .syscall22:
  mov rdi, rsi
  mov rsi, rdx
  mov rdx, rcx
  call sys_pipe_write
  jmp .continue

  .syscall23:
  mov rdi, rsi
  mov rsi, rdx
  call sys_change_priority
  jmp .continue

  .syscall24:
  call sys_split_screen
  jmp .continue

  .syscall25:
  call sys_unsplit_screen

  .syscall26:
  mov rdi, rsi
  call sys_sleep_seconds
  jmp .continue

; EXCEPTIONS 

%macro pushAllRegisters 0
  push rax
  push rbx
  push rcx
  push rdx
  push rdi
  push rsi
  push r15
  push r14
  push r13
  push r12
  push r11
  push r10
  push r9
  push r8
%endmacro

%macro printName 1
  call nextLine
  mov rdi, %1             
  call printf
%endmacro

%macro printValue 0
  mov rsi, convertedString
  call registerValueToString   
  mov rdi, rax
  call printf
%endmacro

%macro exception 1
  push rbp
  mov rbp, rsp

  pushAllRegisters
  call nextLine
  mov rdi, %1             ; print type of error
  call printf
  call nextLine
  mov rdi, registerLabel  ; print Register Values:
  call printf

  printName regRIP
  mov rdi, [rbp + 8]      ; value of RIP
  printValue
  printName regSS
  mov rdi, [rbp + 40]	  ; value of SS
  printValue
  printName regCS
  mov rdi, [rbp + 16]	  ; value of CS
  printValue
  printName regR8
  pop rdi                 ; value of R8 
  printValue
  printName regR9
  pop rdi                 ; value of R9
  printValue
  printName regR10
  pop rdi                 ; value of R10
  printValue
  printName regR11
  pop rdi                 ; value of R11 
  printValue
  printName regR12
  pop rdi                 ; value of R12
  printValue
  printName regR13
  pop rdi                 ; value of R13
  printValue
  printName regR14
  pop rdi                 ; value of R14 
  printValue 
  printName regR15
  pop rdi                 ; value of R15
  printValue
  printName regRSI
  pop rdi                 ; value of RSI 
  printValue
  printName regRDI
  pop rdi                 ; value of RDI
  printValue
  printName regRDX
  pop rdi                 ; value of RDX
  printValue
  printName regRCX
  pop rdi                 ; value of RCX 
  printValue
  printName regRBX
  pop rdi                 ; value of RBX
  printValue
  printName regRAX
  pop rdi                 ; value of RAX
  printValue
  printName regRSP
  mov rdi, [rbp + 32]     ; value of RSP
  printValue
  printName regRBP             
  mov rdi, [rbp]          ; value of RBP (current RBP points to the old one)
  printValue

  mov rsp, rbp
  pop rbp
  call reboot
  iret
%endmacro

;Zero Division Exception
_exception0Handler:
	exception zeroDivision

;Invalid operationException
_exception6Handler:
	exception invalidOp
	
timer_tick:
  int 20h

haltcpu:
	cli
	hlt
	ret

; END OF EXCEPTIONS



section .bss
  aux resq 1
  convertedString resb 20

section .data
  zeroDivision db "Error: Division by zero", 0
  invalidOp db "Error: Invalid opcode", 0
  registerLabel db "Register Values", 0
  regRAX db "RAX: ", 0
  regRBX db "RBX: ", 0
  regRCX db "RCX: ", 0
  regRDX db "RDX: ", 0
  regRSI db "RSI: ", 0
  regRDI db "RDI: ", 0
  regRBP db "RBP: ", 0
  regRSP db "RSP: ", 0
  regRIP db "RIP: ", 0
  regSS db " SS: ", 0
  regCS db " CS: ", 0
  regR8 db "R08: ", 0
  regR9 db "R09: ", 0
  regR10 db "R10: ", 0
  regR11 db "R11: ", 0
  regR12 db "R12: ", 0
  regR13 db "R13: ", 0
  regR14 db "R14: ", 0
  regR15 db "R15: ", 0



