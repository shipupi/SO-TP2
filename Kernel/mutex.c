#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "scheduler/PCB.h"
#include "scheduler/process.h"
#include "drivers/vesaDriver.h"
#include "interrupts.h"
#include "string.h"
#include <naiveLegacy/naiveClock.h>
#include <naiveLegacy/naiveConsole.h>
#include "ipc/mutex.h"
#include "include/lib.h"
#include "include/interrupts.h"
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
    m.value = MUT_UNLOCKED;
    arrMUT[mId] = m;
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
    }
    arrMUT[mId] = m;

	return 0;
}

int mut_request(char * id){
	int mId = findIdMUT(id);
    if (mId == -1){
        return -1;
    }
    MUT m = arrMUT[mId];
    // exhange 1, m.value
    int a = 1;
    // exc(a,m.value)
    if (m.value == MUT_LOCKED)
    {
        m.waitPids[m.waiting] = pid();
        m.waiting += 1;
        arrMUT[mId] = m;
        printInt(pid());
        ipc_sleep();
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
