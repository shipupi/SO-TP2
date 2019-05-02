#include <stdint.h>
#include "memoryManager.h"
#include "PCB.h"
#include "vesaDriver.h"


// Process Control Block
	

#define MAXPROCESSES 256
#define PROCESSSTACKSIZE 4096

static int currentPID = 0;


static PCB processes[MAXPROCESSES]; 

void * schedule(void * oldStack) {
	// printWhiteString("test");
	return  processes[0].stackAddress;
}

// Returns pid?
uint8_t addProcess(void * entryPoint) {
	printWhiteString("add");
	printInt(currentPID);
	printWhiteString("add2");
	struct PCB newPCB;
	void * newStack = requestMemorySpace(4096);
	newPCB.pid = 1;
	newPCB.stackAddress = newStack;
	newPCB.status = PCB_READY;
	processes[currentPID] = newPCB;
	currentPID++;
	return 1;
}

// Ends the process
void endProcess(void * stackAddress) {
	printWhiteString("end");
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
		printWhiteString("  -  ");
		printUint((uint64_t) (uintptr_t) processes[i].stackAddress);
		printWhiteString("  -  ");
		printInt(processes[i].status);
		nextLine();
	}
} 
