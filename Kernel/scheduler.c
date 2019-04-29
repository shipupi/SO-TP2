#include <stdint.h>


// Process Control Block
typedef struct PCB {
	uint8_t pid;
	void * stackAddress;
	uint8_t status;
} PCB;


#define MAXPROCESSES 256

PCB processes[MAXPROCESSES]; 

void * schedule(void * oldStack) {
	return  processes[0].stackAddress;
}

// Returns pid?
uint8_t addProcess(void * stackAddress) {
	return 1;
}

// Ends the process
void endProcess(void * stackAddress) {
	return;
}

PCB * listProcesses() {
	return processes;
} 