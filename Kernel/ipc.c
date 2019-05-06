#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "include/lib.h"
#include "ipc/ipc.h"
#include "include/string.h"
#include "include/drivers/vesaDriver.h"
#include "include/drivers/vesaDriver.h"
#include "include/interrupts.h"

IPC arrIPC[MAX_IPCS];

int IPCCounter = 0;

int ipc_create (char * id, uint64_t size){
    int i;
    struct IPC newIPC;
    void * address = requestMemorySpace(size * BLOCK_SIZE);
    memcpy(newIPC.id,id,ID_SIZE);
    newIPC.address = address;
    newIPC.write = 0;
    newIPC.read = 0;
    newIPC.unread = 0;
    newIPC.free = size;
    newIPC.waiting = 0;
    for (i = 0; i < MAX_QUEUE; ++i)
    {
        newIPC.waitPids[i] = -1;
    }
    arrIPC[IPCCounter] = newIPC;
    IPCCounter++;
	return 1;
}

int findId( char * id) {
    int foundId = -1;
    for (int i = 0; i < IPCCounter; ++i)
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
    if (ipcId == -1){
        return;
    }
    IPC ipc = arrIPC[ipcId];

    if (messageSize > BLOCK_SIZE) {
        // No entra, retornamos
        return;
    }

    if (ipc.free == 0)
    {
        // No hay bloques libres en el ipc, retornamos
        return;
    }

    void * writeAddress = ipc.address + BLOCK_SIZE * ipc.write;
    memset(writeAddress, 0, BLOCK_SIZE);
    memcpy(writeAddress, string, messageSize);

    ipc.write = (ipc.write + 1) % ipc.size;
    ipc.free -= 1;
    ipc.unread += 1;
}

void ipc_read(char * id,char * string,uint64_t messageSize){
    int ipcId = findId(id);
    if ( ipcId == -1)
    {
        return;
    }
    
    IPC ipc = arrIPC[ipcId];

    while (!ipc.unread)
    {
        _syscall(16); // Syscall de sleep para dormir ( en teoria vuelve aca despues, hay q probarlo)
    }
    // Hay bloques sin leer
    memcpy(string, ipc.address + BLOCK_SIZE * ipc.read, messageSize);
    ipc.free += 1;
    ipc.unread -= 1;
    ipc.read = (ipc.read + 1) % ipc.size;
    
}

void ipc_list(){
    int i;
    nextLine();
    printWhiteString("id | addresss | IPCcounter | Read/Unread");
    nextLine();
    for (i = 0; i < IPCCounter ; ++i)
    {
        printWhiteString(arrIPC[i].id);
        printWhiteString("   |     ");

        printUint((uint64_t) (uintptr_t) arrIPC[i].address);
        printWhiteString("    |    ");

        printInt(arrIPC[i].IPCcounter);
        printWhiteString("    |    ");

        printUint((uint64_t) (uintptr_t)arrIPC[i].read);
        printWhiteString("    |    ");

        printUint((uint64_t) (uintptr_t)arrIPC[i].unread);

        nextLine();
    }
}



