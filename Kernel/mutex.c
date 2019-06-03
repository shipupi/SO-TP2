#include <stdint.h>
#include "include/memoryManager/memoryManager.h"
#include "include/drivers/vesaDriver.h"
#include "include/interrupts.h"
#include "include/string.h"
#include "include/ipc/mutex.h"
#include "include/lib.h"
#include "include/utils.h"
#include "include/scheduler/scheduler.h"
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
    int pId;
    pId = pid();
    // printf("adding pid to queue:"); printn(pId); 
    for (int i = 0; i < arrMUT[mId].waiting; ++i)
    {
        if (arrMUT[mId].waitPids[i] == pId)
        {
            return;
        }
    }
    arrMUT[mId].waitPids[arrMUT[mId].waiting] = (uint64_t)pId;
    arrMUT[mId].waiting += 1;
    return;


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
    arrMUT[mId].value = MUT_UNLOCKED;
    int nextPid = -1;
	if (arrMUT[mId].waiting > 0) {
        nextPid = arrMUT[mId].waitPids[0];
        arrMUT[mId].waitPids[0] = -1;
        for (int i = 1; i < arrMUT[mId].waiting - 1; ++i)
        {
            arrMUT[mId].waitPids[i -1 ] = arrMUT[mId].waitPids[i];
        }
        arrMUT[mId].waiting -= 1;
        wakePID(nextPid);
    }
	return 0;
}

int mut_request(char * id){
	int mId = findIdMUT(id);
    if (mId == -1){
        return -1;
    }

    
    while(1) {
        int a = MUT_LOCKED;
        a = exch(a, (uintptr_t)&arrMUT[mId].value);
        if (a == MUT_LOCKED) {
            addProcessToQueue(mId);
            ipc_sleep();
        } else {
            return 1;
        }
    }
}

int mut_delete(char * id){
	printf("Deleting mut (not implemented)\n");
	return 0;
}

void mut_list(){
	int i;
    int j;
    printf("\n");
    printf("id | value | waiting");
    printf("\n");
    //printn(MUTcounter);
    for (i = 0; i < MUTcounter ; ++i)
    {
        printf(arrMUT[i].id);
        printf("   |     ");
        printf(arrMUT[i].value == MUT_LOCKED? "lck" : "unlck");
        printf("    |    ");

        printn((uint64_t) (uintptr_t)arrMUT[i].waiting);
        //printf("    |    ");

        if (arrMUT[i].waiting > 0)
        {
            printf("\n");
            printf("Waiting PIDS:");
            for (j = 0; j < arrMUT[i].waiting; ++j)
            {
                printn(arrMUT[i].waitPids[j]);
                printf(", ");
            }
        }

        printf("\n");

    }
}
