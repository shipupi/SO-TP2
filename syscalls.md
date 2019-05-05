#Syscalls TP2

## Generales

###  Sleep()

Pone un proceso a dormir

## IPCs

### create_ipc(char * id, uint64_t size)

Crea un IPC Con ID id y direccion de tamanio de memoria size

### ipc_write(char * id,  char * string, uint64_t messageSize)

Escribe en el IPC un string con tamanio messagesize  ( va a haber que hacer un memcpy del string al buffer del ipc)
Tambien va a haber q llevar un contador de cantidad de caracteres escritos, para saber cuando se puede desbloquear en el read

### ipc_read (char * id, char * buffer, messageSize)

Lee del IPC un mensaje de tamanio messageSize. Bloquea al proceso hasta que haya messageSize caracteres escritos en el buffer

