#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "include/lib.h"
#include "ipc/ipc.h"
#include "include/string.h"
#include "include/drivers/vesaDriver.h"

#define N 20


IPC arrIPC[N];

int ipcIndex = 0;
int IPCCounter = 0;

<<<<<<< HEAD
int findId(char * id) {
=======
int ipc_create (char * id, uint64_t size){
    struct IPC newIPC;
    void * address = requestMemorySpace(size);
    memcpy(newIPC.id,id,ID_SIZE);
    newIPC.address = address;
    newIPC.write = 0;
    newIPC.read = 0;
    newIPC.unread = 0;
    newIPC.free = size;
    arrIPC[IPCCounter] = newIPC;
    IPCCounter++;
	return 1;
}

int findId( char * id) {
>>>>>>> c2653375df640149c1e645d44428c9a4c71dc22b
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

int ipc_create (char * id, uint64_t size){
    if(findId(id)==-1){
        struct IPC newIPC;
        void * address = requestMemorySpace(size);
        memcpy(newIPC.id,id,ID_SIZE);
        newIPC.address = address;
        newIPC.IPCcounter = IPCcounter;
        newIPC.read = 0;
        newIPC.unread = 0;
        arrIPC[IPCcounter] = newIPC;
        IPCcounter++;
        return 1;
    }
	return -1;
}


void ipc_write(char * id,char * string,uint64_t messageSize){
    int ipcId = findId(id);
    IPC ipc = arrIPC[ipcId];

    if (messageSize > ipc.size) {
        // No entra, retornamos
        return;
    }

    if (messageSize > ipc.free) {
        // No entra, retornamos
        return;
    }

    if (ipc.write + messageSize > ipc.size)
    {
        // Hay q copiar la mitad y la otra mitad al principio
        uint64_t endSize = ipc.size - ipc.write;
        uint64_t startSize = messageSize - endSize;
        memcpy(ipc.address + ipc.write, string, endSize);
        memcpy(ipc.address, string + endSize, startSize);
        ipc.write = startSize;
    } else {
        // hay lugar para todo, vamos a copiar el string al buffer
        memcpy(ipc.address + ipc.write, string, messageSize);
        ipc.write += messageSize;
    }

    ipc.free -= messageSize;
    ipc.unread += messageSize;
}

void ipc_read(char * id,char * string,uint64_t messageSize){

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


<<<<<<< HEAD
=======

>>>>>>> c2653375df640149c1e645d44428c9a4c71dc22b
