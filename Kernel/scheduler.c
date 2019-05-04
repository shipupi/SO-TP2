#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "scheduler/PCB.h"
#include "drivers/vesaDriver.h"


// Process Control Block
	

#define MAXPROCESSES 256
#define PROCESSSTACKSIZE 4096

static int currentPID = 0;


static PCB processes[MAXPROCESSES]; 

void * schedule(void * oldStack) {
	return  processes[0].stackAddress;
}

// Returns pid?
uint8_t addProcess(void * entryPoint , uint64_t priority , char name , uint8_t foreground , uint64_t size){
	struct PCB newPCB;
	void * newStack = requestMemorySpace(PROCESSSTACKSIZE);
	newPCB.pid = currentPID;
	newPCB.stackAddress = newStack;
	newPCB.status = PCB_READY;
	newPCB.priority = priority;
	newPCB.name = name;
	newPCB.foreground = foreground;
	newPCB.size = size;
	processes[currentPID] = newPCB;
	currentPID++;
	return 1;
}

// Ends the process
void endProcess(int pid) {
	processes[pid].status = PCB_ENDED;
	freeMemorySpace(processes[pid].stackAddress, PROCESSSTACKSIZE);
	return;
}

void listProcesses() {
	int i;
	nextLine();
	printWhiteString("PID | Stack Addresss | Status | Priority | Nombre | Foreground | Reserved Memory ");
	nextLine();
	for (i = 0; i < currentPID; ++i)
	{
		printUint(processes[i].pid);
		printWhiteString("   | 	   ");

		printUint((uint64_t) (uintptr_t) processes[i].stackAddress);
		printWhiteString("    |    ");

		printInt(processes[i].status);
		printWhiteString("    |    ");

		printInt(processes[i].priority);
		printWhiteString("    |    ");

		printUint(processes[i].name);
		printWhiteString("    |    ");

		printUint(processes[i].foreground);
		printWhiteString("    |    ");

		printUint(processes[i].size);

		nextLine();
	}
} 




