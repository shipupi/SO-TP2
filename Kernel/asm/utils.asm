


section .text

GLOBAL int20
GLOBAL exch
GLOBAL halt

int20:
  int 20h


exch:
	; rdi = value
	; rsi = memPos
	xchg rdi, rsi
	ret


halt: 
	hlt