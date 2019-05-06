#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "scheduler/PCB.h"
#include "scheduler/process.h"
#include "drivers/vesaDriver.h"
#include "interrupts.h"
#include <naiveLegacy/naiveClock.h>
#include <naiveLegacy/naiveConsole.h>
#include "ipc/mutex.h"
#include "include/lib.h"

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
	printWhiteString("mut_create");
	nextLine();
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

int mut_request(char * id){
	printWhiteString("mut_request");
	nextLine();
	return 0;
}

int mut_release(char * id){
	printWhiteString("mut_release");
	nextLine();
	return 0;
}

int mut_delete(char * id){
	printWhiteString("mut_delete");
	nextLine();
	return 0;
}

void mut_list(){
	printWhiteString("mut_list");
	nextLine();
	int i, j;
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
