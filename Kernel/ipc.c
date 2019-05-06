#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "include/lib.h"
#include "ipc/ipc.h"
#include "include/string.h"
#include "include/drivers/vesaDriver.h"

#define N 20


IPC arrIPC[N];

int ipcIndex = 0;
int IPCcounter = 0;

int findId(char * id) {
    int foundId = -1;
    for (int i = 0; i < IPCcounter; ++i)
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
        // No entra, retorneamos
        return;
    }

    if (ipc.write + messageSize > ipc.size) {

    }
}

void ipc_read(char * id,char * string,uint64_t messageSize){

}

void ipc_list(){
    int i;
    nextLine();
    printWhiteString("id | addresss | IPCcounter | Read/Unread");
    nextLine();
    for (i = 0; i < IPCcounter ; ++i)
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


