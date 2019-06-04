#include <stdint.h>
#include "include/memoryManager/memoryManager.h"
#include "scheduler/PCB.h"
#include "scheduler/process.h"
#include "drivers/vesaDriver.h"
#include "interrupts.h"
#include "string.h"
#include "ipc/ipc.h"
#include "include/drivers/time.h"
#include "include/utils.h"
#include "include/lib.h"
#include "include/scheduler/scheduler.h"
#include <naiveLegacy/naiveClock.h>
#include <naiveLegacy/naiveConsole.h>



// Process Control Block
	



static int PIDCounter = 0;
static int activeProcess = -1;
static int m_ticket = 0;
typedef int (*EntryPoint)();

int rand(int n){
	int runi = (ticks_elapsed()*31*17*11*13 *37)%(1000);
	return runi;
}


static PCB processes[MAXPROCESSES];
static int ticket[MAXPROCESSES][MAXPROCESSES]; 


int chooseNextProcess2(int ap[], int n) {
	int chosen = ap[0];
	for (int i = 0; i < n; ++i)
	{
		if (ap[i] == activeProcess && i != n-1) {
			// Si no estoy en el ultimo, devuelvo el siguiente al q estoy
			return ap[i+1];
		}
	}
	// Si estoy en el ultimo (o en uno q ya no esta activo) devuelvo el primero
	return chosen;
}

int chooseNextProcess(int ap[], int n) {
	
	int priority[n];
	int i,z;
	int winner = 0;
	int winner_ticket = (rand(n)%m_ticket)+1;
	
	//initialize prioritys
	int t = 0;
	int index[n];
	for (i = 0; i < MAXPROCESSES; ++i)
	{
		if (processes[i].status == PCB_READY)
		{
	
			priority[t] = processes[i].priority;
			index[t] = i;
			t++;
		}
	}
	
	for(i =0;i<n;i++){
        for(z=0;z<priority[i];z++){
            if(ticket[i][z]==winner_ticket){
                winner=i;
            }
        }
    }

	for (i = 0; i < MAXPROCESSES; ++i)
	{
		if (processes[i].status == PCB_READY)
		{
	
			priority[t] = processes[i].priority;
			index[t] = i;
			t++;
		}
		

	}

    return index[winner];
}

void * schedule(void * oldStack) {

	// Si no hay procesos creados, devuelvo el stack q estaba ( seguramente era del kernel)
	if (PIDCounter  == 0)
	{
		pl("PID Counter = 0");
		halt();
	}

	int i;
	int n = 0;
	int ap[MAXPROCESSES];
	for (i = 0; i < MAXPROCESSES; ++i)
	{
		if (processes[i].status == PCB_READY)
		{
			ap[n] = i;
			n++;
		}
	}


	// Si no hay processescesos activos, hago un halt
	// Pero hay q ver como arreglo el stack?
	// Tengo la cantidad de procesos activos y los tengo metidos en un array
	if (activeProcess != -1) {
		// Piso el stack del proceso anterior
		// nextLine();
		// printf("Saving stack of process: "); 
		// printn(activeProcess);
		// printf(". Address: ");
		// printn((uintptr_t)oldStack);
		// nextLine();

		// Guardando stack
		if(oldStack > (processes[activeProcess].baseAddress + PROCESSSTACKSIZE)) {
			printWhiteString("Stack OVerflow!!! Pid: ");
			printInt(activeProcess);
			printWhiteString("\n");
		}
		processes[activeProcess].stackAddress = oldStack;
	} 


	if (n == 0)
	{
		activeProcess = 0;
	} else {
		activeProcess = chooseNextProcess2(ap, n);

	}

	// Setteo el nuevo activeprocess con el que me toco
	return processes[activeProcess].stackAddress;
}

void lottery(){
	int i,z,t;
	int n = 0;
	for (i = 0; i < MAXPROCESSES; ++i)
	{
		if (processes[i].status == PCB_READY)
		{
			n++;
		}
	}

	int lottery[MAXPROCESSES];
	int p=1;
	m_ticket=0;
	int priority[n];

	//initialize prioritys
	t=0;
	for (i = 0; i < MAXPROCESSES || t != n; ++i)
	{
		if (processes[i].status == PCB_READY)
		{
			priority[t] = processes[i].priority;
			t++;
		}
	}


	for(i=0;i<n;i++)
	{
		lottery[i]=(priority[i])+1;

		for (z=0;z<lottery[i];z++) 
		{
			m_ticket = p;
            ticket[i][z] = p++;            
        }
	}
	
}

// Returns pid?
uint8_t addProcess(void * entryPoint , uint64_t priority , uint8_t foreground , uint64_t size, char * fdIn, char * fdOut){
	struct PCB newPCB;
	void * newStack = requestMemorySpace(PROCESSSTACKSIZE);
	newPCB.stackAddress = newStack;
	newPCB.baseAddress = newStack;
	fillStackFrame (newPCB,entryPoint);
	newPCB.pid = PIDCounter;
	newPCB.status = PCB_READY;
	newPCB.priority = priority;
	newPCB.foreground = foreground;
	newPCB.size = size;
	if (foreground == PCB_BACKGROUND && strcmp(fdIn, DEFAULT_FDIN) == 0) {
		memcpy(newPCB.fdIn, INVALID_FD, FD_NAME_SIZE);
	} else {
		memcpy(newPCB.fdIn, fdIn, FD_NAME_SIZE);
	}
	memcpy(newPCB.fdOut, fdOut, FD_NAME_SIZE);
	processes[PIDCounter] = newPCB;
	PIDCounter++;
	lottery();
	return PIDCounter -1;
}

/*

void editPriority(uint64_t pid , int priority){
	
}

*/

void changePriority(uint64_t pid , int priority){
	processes[pid].priority = priority;
	lottery();
	return;
}



// Ends the process
void endProcess(int pid) {
	processes[pid].status = PCB_ENDED;
	// printWhiteString("closing program ");printInt(pid);printWhiteString("\n");
	freeMemorySpace(processes[pid].baseAddress, PROCESSSTACKSIZE);
	// listProcesses();
	return;
}

void runProcess(uintptr_t entryPoint) {
	((EntryPoint)entryPoint)();
	endProcess(activeProcess);
	timer_tick();
}


void listProcesses() {
	int i;
	printWhiteString("\n");
	printWhiteString("PID | Stack Addresss | Status | Priority  | Foreground | Reserved Memory | FDIN   | FDOUT");
	printWhiteString("\n");
	for (i = 0; i < PIDCounter; ++i)
	{
		if (processes[i].status == PCB_ENDED)
		{
			 continue;
		}
		printInt(processes[i].pid);
		printWhiteString("   | 	   ");

		printInt((uint64_t) (uintptr_t) processes[i].stackAddress);
		printWhiteString("    |    ");
		switch(processes[i].status) {
			case PCB_READY:
				printWhiteString("rdy");
				break;
			case PCB_LOCK:
				printWhiteString("lck");
				break;
			case PCB_ENDED:
				printWhiteString("end");
				break;
		}
		printWhiteString(" |    ");
		printInt(processes[i].priority);
		printWhiteString("      |    ");
		printWhiteString(processes[i].foreground == PCB_FOREGROUND? "fg" : "bg");
		printWhiteString("      |    ");		
		printInt(processes[i].size);
		printWhiteString("           |     ");
		printWhiteString(processes[i].fdIn);
		printWhiteString("   |    ");
		printWhiteString(processes[i].fdOut);
		printWhiteString("\n");
	}
}


// Sends active process to sleep
void sleep() {
	processes[activeProcess].status = PCB_LOCK;
}


void sleepPID(int pid) {
	processes[pid].status = PCB_LOCK;
}

void wakePID(int pid) {
	if (PIDCounter >= pid + 1 && processes[pid].status == PCB_LOCK)
	{
		processes[pid].status = PCB_READY;
	}
}

int pid() {
	return activeProcess;
}

void process_status(void * pcbAddr) {
	PCB p = processes[activeProcess];
	memcpy(pcbAddr,(void *)(uintptr_t) &p, (int) sizeof(PCB));
}



char * getFdIn() {
	if(activeProcess == -1) return DEFAULT_FDIN;
	return processes[activeProcess].fdIn;	
}

char * getFdOut() {
	if(activeProcess == -1) return DEFAULT_FDOUT;
	return processes[activeProcess].fdOut;
}