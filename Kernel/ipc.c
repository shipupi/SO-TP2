 #include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "include/lib.h"
#include "ipc/ipc.h"
#include "ipc/mutex.h"
#include "include/string.h"
#include "include/drivers/vesaDriver.h"
#include "include/interrupts.h"
#include "include/scheduler/scheduler.h"

IPC arrIPC[MAX_IPCS];

int ipcIndex = 0;
int IPCcounter = 0;


int findId( char * id) {
    int foundId = -1;
    for (int i = 0; i < IPCcounter; ++i)
    {
        if (strcmp(arrIPC[i].id, id) == 0) {
            foundId = i;
            return i;
            break;
        }
    }
    return foundId;
}

int ipc_create (char * id, uint64_t size){
    if(findId(id)==-1){
        int i;
        struct IPC newIPC;
        void * address = requestMemorySpace(size * BLOCK_SIZE);
        memcpy(newIPC.id,id,ID_SIZE);
        newIPC.address = address;
        newIPC.write = 0;
        newIPC.read = 0;
        newIPC.unread = 0;
        newIPC.free = size;
        newIPC.size = size;
        mut_create(id);
        newIPC.waiting = 0;
        for (i = 0; i < MAX_QUEUE; ++i)
        {
            newIPC.waitPids[i] = -1;
        }
        arrIPC[IPCcounter] = newIPC;
        newIPC.IPCcounter = IPCcounter;
        IPCcounter++;
        return 1;
    }
	return -1;
}


void ipc_write(char * id,char * string,uint64_t messageSize){
    int ipcId = findId(id);
    if (ipcId == -1){
        return;
    }
    if (messageSize > BLOCK_SIZE){
        // No entra, retornamos
        return;
    }

    mut_request(id);


    //  ZONA CRITICA 
    IPC ipc = arrIPC[ipcId];
    if (ipc.free == 0){
        // No hay bloques libres en el ipc, retornamos
        mut_release(id);
        return;
    }
    void * writeAddress = ipc.address + BLOCK_SIZE * ipc.write;
    memset(writeAddress, 0, BLOCK_SIZE);
    memcpy(writeAddress, string, messageSize);

    if (ipc.waiting > 0) {
        int nextPid = ipc.waitPids[0];
        ipc.waitPids[0] = -1;
        for (int i = 1; i < ipc.waiting - 1; ++i)
        {
            ipc.waitPids[i -1 ] = ipc.waitPids[i];
        }
        ipc.waiting -= 1;
        wakePID(nextPid);
    }

    ipc.write = (ipc.write + 1) % ipc.size;
    ipc.free -= 1;
    ipc.unread += 1;
    arrIPC[ipcId] = ipc;

    // FIN DE ZONA CRITICA
    mut_release(id);
}

void ipc_read(char * id,char * string,uint64_t messageSize){
    int ipcId = findId(id);
    if ( ipcId == -1)
    {
        return;
    }
    
    mut_request(id);
    // ZONA CRITICA
    IPC ipc = arrIPC[ipcId];

    if (!ipc.unread)
    {
        ipc.waitPids[ipc.waiting] = pid();
        ipc.waiting += 1;
        arrIPC[ipcId] = ipc;
        mut_release(id);
        ipc_sleep(); // Pongo el proceso a dormir hasta q lo despierten (por ejemplo con sys_write)
        mut_request(id);
    } else 
    ipc = arrIPC[ipcId];
    // Hay bloques sin leer
    memcpy(string, ipc.address + BLOCK_SIZE * ipc.read, messageSize);
    ipc.free += 1;
    ipc.unread -= 1;
    ipc.read = (ipc.read + 1) % ipc.size;
    arrIPC[ipcId] = ipc;

    // FIN ZONA CRITICA
    mut_release(id);
}

void ipc_list(){
    int i, j;
    nextLine();
    printWhiteString("id | addresss | IPCcounter | Read | Write | Unread | Free | Size | Waiting");
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
        printUint((uint64_t) (uintptr_t)arrIPC[i].write);
        printWhiteString("    |    ");

        printUint((uint64_t) (uintptr_t)arrIPC[i].unread);
        printWhiteString("    |    ");
        printUint((uint64_t) (uintptr_t)arrIPC[i].free);
        printWhiteString("    |    ");
        printUint((uint64_t) (uintptr_t)arrIPC[i].size);
        printWhiteString("    |    ");
        printUint((uint64_t) (uintptr_t)arrIPC[i].waiting);

        if (arrIPC[i].waiting > 0)
        {
            nextLine();
            printWhiteString("Waiting PIDS:");
            for (j = 0; j < arrIPC[i].waiting; ++j)
            {
                printInt(arrIPC[i].waitPids[j]);
                printWhiteString(", ");
            }
        }
        nextLine();
    }
}





