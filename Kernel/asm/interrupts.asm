
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

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
EXTERN printWhiteString
EXTERN registerValueToString
EXTERN nextLine
EXTERN reboot

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
%endmacro

%macro popState 0
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
	irqHandlerMaster 0

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
	push rbp
	mov rbp, rsp

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

  cmp rdi, 0x0A   ; syscall de unbeep
  je .syscall0A

  cmp rdi, 0x0B   ; syscall de unbeep
  je .syscall0B

.continue:
	mov rsp, rbp
	pop rbp
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
  call printWhiteString
%endmacro

%macro printValue 0
  mov rsi, convertedString
  call registerValueToString   
  mov rdi, rax
  call printWhiteString
%endmacro

%macro exception 1
  push rbp
  mov rbp, rsp

  pushAllRegisters
  call nextLine
  mov rdi, %1             ; print type of error
  call printWhiteString
  call nextLine
  mov rdi, registerLabel  ; print Register Values:
  call printWhiteString

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