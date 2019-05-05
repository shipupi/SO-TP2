#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "include/lib.h"
#include "ipc/ipc.h"
#include "include/string.h"

#define N 20


IPC arrIPC[N];

int ipcIndex = 0;

int ipc_create (char * id, uint64_t size){
    struct IPC newIPC;
    void * address = requestMemorySpace(size);
    memcpy(newIPC.id,id,ID_SIZE);
    newIPC.address = address;
    arrIPC[ipcIndex] = newIPC;
    ipcIndex++;
	return 1;
}

int findId( char * id) {
    int foundId = -1;
    for (int i = 0; i < ipcIndex; ++i)
    {
        if (strcmp(arrIPC[i].id, id) == 0) {
            foundId = i;
            break;
        }
    }
    return foundId;
}

void ipc_write(char * id,char * string,uint64_t messageSize){
    int ipcId = findId(id);
    IPC ipc = arrIPC[ipcId];

    if (messageSize > ipc.size) {
        // No entra, retorneamos
        return;
    }

    if (ipc.write + messageSize > ipc.size)
    {
        // No me entra en el espacio restante, se podria hacer q vuelva al principio pero por ahora no hay tiempo
        return;
    }

    




}
void ipc_read(char * id,char * string,uint64_t messageSize){

}

