


section .text

GLOBAL int20
GLOBAL exch
GLOBAL halt

int20:
  int 20h


exch:
	; rdi = value
	; rsi = memPos
	mov rax, rdi
	xchg rax, [rsi]
	ret


halt: 
	sti
	mov al, 20h
	out 20h, al
	hlt