#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "include/lib.h"
#include "ipc/ipc.h"

#define N 20


IPC arrIPC[N];

int i = 0;

int ipc_create (char * id, uint64_t size){
    struct IPC newIPC;
    void * address = requestMemorySpace(size);
    memcpy(newIPC.id,id,ID_SIZE);
    newIPC.address = address;
    newIPC.i = i;
    arrIPC[i] = newIPC;
    i++;
	return 1;
}

void ipc_write(char * id,char * string,uint64_t messageSize){

}
void ipc_read(char * id,char * string,uint64_t messageSize){

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






