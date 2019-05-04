# Agregar una nueva syscall ( o modificar una existente)

## Kernel Space

1. Agregar a Kernel/systemCalls.c

	Aca se agrega lo que hace la syscall, por ejemplo 

	```c
	void sys_freeMemorySpace (void * freeBaseAddress,int32_t size) {
		freeMemorySpace(freeBaseAddress,size);
	}
	```

	Notar que empieza con 'sys_'

2. Agregar el .h de la funcion en Kernel/include/systemCalls.h

```asm
void sys_freeMemorySpace (void * freeBaseAddress,int32_t size);
```

3. Agergarlas a Kernel/asm/interrupts.asm

Primero, definir el EXTERN

```asm
EXTERN sys_freeMemorySpace
```

Despues Agregarlas a la lista de syscalls . El numero 0x0B es el numero de syscall que va a tener la nueva syscall
```asm
  cmp rdi, 0x0B   ; syscall de freeMemorySpace
  je .syscall0B
```

Por ultimo, definiar la funcion .syscall0B abajo, como el primer registro viene con el numero de syscall, y nuestra funcion no lo usa, tenemos que mover los parametros un registro 

```asm

.syscall07:
	mov rdi, rsi	; re-ordering the arguments to send to sys_pixel
	mov rsi, rdx
	mov rdx, rcx
	mov rcx, r8
	mov r8, r9
	call sys_pixel
	jmp .continue
```

En este ejemplo, la syscall 7 (void sys_pixel(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b))
Tiene 5 parametros, por lo cual mueve 5 registros, en caso de que solo tengamos un parametro, hacemos un solo mov

```asm
.syscall0A:
  mov rdi, rsi
  call sys_requestMemorySpace
  jmp .continue
```

Siempre manteniendo el orden (primero el rdi,rsi despues el rsi, rdx... y asi cuantos mas parametros haya)

## User Space


4. Agregar la funcion con los parametros en el .h Userland/SampleCodeModule/include/syscalls.h

```asm
void os_freeMemorySpace (void * freeBaseAddress,int32_t size);
```

Notar que las syscalls en Userland les ponemos os_ al principio

5. Userland/SampleCodeModule/asm/syscalls.asm

Definir arriba de todo la funcion como global

```asm
GLOBAL os_freeMemorySpace
```

Y despues agregar la funcion, que es la que llama a int80

```asm
os_freeMemorySpace:
	start
	mov rdx, rsi
	mov rsi,rdi
	mov rdi, 0x0B
	int 80h
	finish
```

Notar que este hace los movs inversos al asm anterior, y el último de todos es el que pone 0x0B (numero de syscall) en rdi
