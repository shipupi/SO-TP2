#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "scheduler/PCB.h"
#include "scheduler/process.h"
#include "drivers/vesaDriver.h"


// Process Control Block
	

#define MAXPROCESSES 256
#define PROCESSSTACKSIZE 4096

static int currentPID = 0;


static PCB processes[MAXPROCESSES]; 

void * schedule(void * currentStack) {
	return processes[0].stackAddress;
}

// Returns pid?
uint8_t addProcess(void * entryPoint) {
	struct PCB newPCB;
	void * newStack = requestMemorySpace(PROCESSSTACKSIZE);
	newPCB.stackAddress = newStack;
	fillStackFrame (newPCB,entryPoint);
	newPCB.pid = currentPID;
	newPCB.status = PCB_READY;
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
	printWhiteString("PID | Stack Addresss | status");
	nextLine();
	for (i = 0; i < currentPID; ++i)
	{
		printUint(processes[i].pid);
		printWhiteString("   | 	   ");
		printUint((uint64_t) (uintptr_t) processes[i].stackAddress);
		printWhiteString("    |    ");
		printInt(processes[i].status);
		nextLine();
	}
} 
