#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "scheduler/PCB.h"
#include "scheduler/process.h"
#include "drivers/vesaDriver.h"
#include "interrupts.h"
#include "include/drivers/time.h"
#include <naiveLegacy/naiveClock.h>
#include <naiveLegacy/naiveConsole.h>



// Process Control Block
	

#define MAXPROCESSES 256
#define PROCESSSTACKSIZE 4096

static int PIDCounter = 0;
static int activeProcess = -1;
static int m_ticket = 0;

typedef int (*EntryPoint)();

int rand(int n){
	return ticks_elapsed();
}


static PCB processes[MAXPROCESSES];
static int ticket[MAXPROCESSES][MAXPROCESSES]; 
//static int lottery[MAXPROCESSES];


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
	
	//int ticket[n][MAXPROCESSES]; // maximum required
	int lottery[MAXPROCESSES];
	int p=1;
	int priority[n];
	int i,z;
	int winner = 0;
	int winner_ticket = (rand(n)%m_ticket)+1;
	//printUint(winner_ticket);
	//int index[n];
	/*pl("el m_tickets de choose ");
	printUint(m_ticket);
	pl(" ");
	int winner_ticket = (rand(n)%m_ticket)+1;
	pl(" el gandor es ");
	printUint(winner_ticket);
	pl(" ");*/
	//printUint(winner_ticket);
	//printUint(m_ticket);

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
                //ticket[i][z] = -1;
            }
        }
    }

    //initialize prioritys
	//int t = 0;
	//int index[n];
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
		return oldStack;
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
	if (n == 0)
	{
		// sleep?
	}

	// Tengo la cantidad de procesos activos y los tengo metidos en un array
	if (activeProcess != -1) {
		// Piso el stack del proceso anterior
		processes[activeProcess].stackAddress = oldStack;
	} 
	// Setteo el nuevo activeprocess con el que me toco
	activeProcess = chooseNextProcess(ap, n);

	return processes[activeProcess].stackAddress;
}

void lottery(){
	int i,z;
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
	int lottery[MAXPROCESSES];
	int p=1;
	m_ticket=0;
	int priority[n];
	
	int winner = 0;

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
uint8_t addProcess(void * entryPoint , uint64_t priority , char name , uint8_t foreground , uint64_t size){
	struct PCB newPCB;
	void * newStack = requestMemorySpace(PROCESSSTACKSIZE);
	newPCB.stackAddress = newStack;
	newPCB.baseAddress = newStack;
	fillStackFrame (newPCB,entryPoint);
	newPCB.pid = PIDCounter;
	newPCB.status = PCB_READY;
	newPCB.priority = priority;
	newPCB.name = name;
	newPCB.foreground = foreground;
	newPCB.size = size;
	processes[PIDCounter] = newPCB;
	PIDCounter++;
	lottery();
	return 1;

}

// Ends the process
void endProcess(int pid) {
	processes[pid].status = PCB_ENDED;
	freeMemorySpace(processes[pid].baseAddress, PROCESSSTACKSIZE);
	return;
}

void runProcess(uintptr_t entryPoint) {
	((EntryPoint)entryPoint)();
	endProcess(activeProcess);
	timer_tick();
}


void listProcesses() {
	int i;
	nextLine();
	printWhiteString("PID | Stack Addresss | Status | Priority | Nombre | Foreground | Reserved Memory ");
	nextLine();
	for (i = 0; i < PIDCounter; ++i)
	{
		if (processes[i].status == PCB_ENDED)
		{
			continue;
		}
		printUint(processes[i].pid);
		printWhiteString("   | 	   ");

		printUint((uint64_t) (uintptr_t) processes[i].stackAddress);
		printWhiteString("    |    ");

		switch(processes[i].status) {
			case PCB_READY:
				printWhiteString("rdy");
				break;
			case PCB_LOCK:
				printWhiteString("lck");
				break;
		}
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


