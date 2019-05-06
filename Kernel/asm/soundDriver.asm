GLOBAL playSound
GLOBAL stopSound


; Uses PIT to play a sound, with the sound frequency as parameter
; it continues to play the sound until stopSound is executed
; I made this with info from https://wiki.osdev.org/PIT

section .data
FREQ dd 9000				; the frequency of the sound

section .text

playSound:
	push rbp
	mov rbp, rsp
	push rax

	xor rax, rax
	mov al, 0xB6			; 0xB6 is 10110110b, we need that value to control the speaker
	out 0x43, al 			; sends the al value to the Mode/Command register

	mov rax, FREQ 		; the frequency number, may be a parameter in later implementations

	movzx rax, al
	out 42h, al
	mov al, ah
	out 42h, al				; output both high and low bytes, 1 byte at a time

	in al, 61h 				; this port allows to control the PC speaker

	or al, 00000011b	; modifies last 2 bits to 1 to enable sound
	out 61h, al				; refreshes new value

	pop rax
	mov rsp, rbp
	pop rbp
	ret

stopSound:
	push rbp
	mov rbp, rsp
	push rax

	xor rax, rax
	mov al, 0xB6			; 0xB6 is 10110110b, sending the value, just in case
	out 0x43, al 			; sends the al value to the Mode/Command register

	in al, 61h				; we get an updated value from 61h,
	and al, 11111100b	; modifies last 2 bits to 0 to disable sound
	out 61h, al

	pop rax
	mov rsp, rbp
	pop rbp
	ret
