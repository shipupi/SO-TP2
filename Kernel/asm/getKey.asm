GLOBAL getKey

section .text


;This should only be called if you know the last bit of 64h (Status Register) is on 1
getKey:
	push rbp
	mov rbp, rsp		;Stack frame

	xor eax, eax		;We are going to use it so we make sure its in zero

	in al, 60h			;We get the code

	mov bl, al			;We save it to use al again

	in al, 64h			;We get Status Register
	and al, 11111110b	;We leave 7 through 1 as is, and make the last bit 0 so we know we pulled the key
	out 64h, al			;Save the changes

	mov al, bl			;We get our Scan Code back to return it

	mov rsp, rbp		;Stack frame
	pop rbp
	ret