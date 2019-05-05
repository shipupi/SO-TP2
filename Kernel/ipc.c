#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "include/lib.h"
#include "ipc/ipc.h"

#define N 20


IPC arrIPC[N];

int IPCcounter = 0;

int ipc_create (char * id, uint64_t size){
    struct IPC newIPC;
    void * address = requestMemorySpace(size);
    memcpy(newIPC.id,id,ID_SIZE);
    newIPC.address = address;
    newIPC.IPCcounter = IPCcounter;
    arrIPC[IPCcounter] = newIPC;
    IPCcounter++;
	return 1;
}

void ipc_write(char * id,char * string,uint64_t messageSize){

}
void ipc_read(char * id,char * string,uint64_t messageSize){

}

void ipc_list(){
    int i;
    nextLine();
    printWhiteString("id | addresss | IPCcounter");
    nextLine();
    for (i = 0; i < IPCcounter ; ++i)
    {
        printWhiteString(arrIPC[i].id);
        printWhiteString("   |     ");

        printUint((uint64_t) (uintptr_t) arrIPC[i].address);
        printWhiteString("    |    ");

        printInt(arrIPC[i].IPCcounter);

        nextLine();
    }
}

uint32_t jenkins_one_at_a_time_hash(char *key, int len)
{
    uint32_t hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}






