GLOBAL registerValueToString

section .bss
      convertedString resb 20   ;where the string will be placed

section .text

registerValueToString:
  push rbp
  mov rbp, rsp

  pushf                   ; push flags
  push rbx
  push r12
  push r13
  push r15

  mov rax, rdi              ; move the value of the register to pass to string to rax
  mov rbx, rsi              ; second argument --> where the string will be stored
  push rsi                  ; store to retrieve the start of the string
  mov rcx, 0x10             ; divisor

  xor rsi, rsi              ; setting my counter to 0
  xor rdi, rdi              ; setting second counter to 0

.loop:
  mov rdx, 0              ;where my remainder will be stored
  div rcx                 ;divide RAX by rcx
  push rdx                ;save the remainder in the stack
  inc rsi                 ;increase counter
  cmp rax, 0              ;if the dividend is 0 then I'm done
  jg .loop                ;if its greater than 0 start the loop again

  cmp rsi, 16             ;if I did not get to 16 it means I had 0 in front
  jl .fill

.store:
  cmp rdi, 16             ;when rdi is 16 it means im done
  jge .end
  pop rdx                 ;takes out the number at the top of the stack
  cmp rdx, 0x9              ;if it is greater than 9 it is a letter
  jg .letter              ;in .converted value is ready to be stored

.number:
  add rdx, '0'            ;turn the remainder NUMBER into a string
  jmp .converted
.letter: 
  add rdx, 55             ;pass hexa for A,B,C,D,E,F to ascii letters
.converted:
  mov [rbx], rdx          ;puts the number in rbx
  inc rbx                 ;moves to the next byte of the string to put the next number
  inc rdi                 ;increase rdi (counter of how many I've already stored)
  jmp .store

.fill:
  mov BYTE [rbx], '0'          ;fill with 0
  inc rbx
  inc rsi
  inc rdi
  cmp rsi, 16             ;if I did not get to 16 it means I had 0 in front
  jl .fill
  jmp .store

.end:
  mov BYTE [rbx], 0

  pop rsi                   ;restore the start of the string
  mov rax, rsi              ;return the answer in RAX

  pop r15
  pop r13
  pop r12
  pop rbx
  popf                      ;restore flags

  mov rsp, rbp            ;undo stack freme
  pop rbp                 ;pop old stack frame value
  ret
