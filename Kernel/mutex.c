#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "drivers/vesaDriver.h"
#include "interrupts.h"
#include "string.h"
#include "ipc/mutex.h"
#include "include/lib.h"
#include "include/utils.h"
#include "include/scheduler/scheduler.h"


MUT arrMUT[MAX_MUTS];

int mutIndex = 0;
int MUTcounter = 0;


int findIdMUT( char * id) {
    int foundId = -1;
    for (int i = 0; i < MUTcounter; ++i)
    {
        if (strcmp(arrMUT[i].id, id) == 0) {
            foundId = i;
            break;
        }
    }
    return foundId;
}

void addProcessToQueue(int mId) {
    // int pid;
    // pid = getPid();
    // for (int i = 0; i < arrMUT[mId].waiting; ++i)
    // {
    //     if (arrMUT[mId].waitPids[i] == pid)
    //     {
    //         return;
    //     }
    // }
    // arrMUT[mId].waitPids[arrMUT[mId].waiting] = pid;
    // arrMUT[mId].waiting += 1;
    // return;


}


int mut_create(char * id){
	if(findIdMUT(id)==-1){
        //pl("entre al if");
        int i;
        struct MUT newMUT;
        
        memcpy(newMUT.id,id,ID_SIZE);
        
        newMUT.value = MUT_UNLOCKED;
        
        newMUT.waiting = 0;
        for (i = 0; i < MAX_QUEUE; ++i)
        {
            newMUT.waitPids[i] = -1;
        }

        arrMUT[MUTcounter] = newMUT;
        
        MUTcounter++;
        
        return 1;
    }
	return -1;

}

int mut_release(char * id){

    int mId = findIdMUT(id);
    if (mId == -1){
        return -1;
    }

    MUT m = arrMUT[mId];
    int nextPid = -1;
	if (m.waiting > 0) {
        nextPid = m.waitPids[0];
        m.waitPids[0] = -1;
        for (int i = 1; i < m.waiting - 1; ++i)
        {
            m.waitPids[i -1 ] = m.waitPids[i];
        }
        m.waiting -= 1;
        wakePID(nextPid);
        m.value = MUT_LOCKED;
    }
    arrMUT[mId] = m;

	return 0;
}

int mut_request(char * id){
	int mId = findIdMUT(id);
    if (mId == -1){
        return -1;
    }
    MUT m;
    
    while(1) {
        int a = MUT_LOCKED;
        exch(a, (uintptr_t)&arrMUT[mId].value);
        if (a == MUT_LOCKED) {
            addProcessToQueue(mId);
            ipc_sleep();
        }
    }    
    m.value = MUT_LOCKED;
    arrMUT[mId] = m;
    return 1;
}

int mut_delete(char * id){
	nextLine();
	return 0;
}

void mut_list(){
	int i;
    // int j;
    nextLine();
    printWhiteString("id | value | waiting");
    nextLine();
    //printInt(MUTcounter);
    for (i = 0; i < MUTcounter ; ++i)
    {
        printWhiteString(arrMUT[i].id);
        printWhiteString("   |     ");

        printUint((uint64_t) (uintptr_t) arrMUT[i].value);
        printWhiteString("    |    ");

        printUint((uint64_t) (uintptr_t)arrMUT[i].waiting);
        //printWhiteString("    |    ");
/*
        if (arrMUT[i].waiting > 0)
        {
            nextLine();
            printWhiteString("Waiting PIDS:");
            for (j = 0; j < arrMUT[i].waiting; ++j)
            {
                printInt(arrMUT[i].waitPids[j]);
                printWhiteString(", ");
            }
        }
*/
        nextLine();

    }
}
