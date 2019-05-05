#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "scheduler/PCB.h"
#include "scheduler/process.h"
#include "drivers/vesaDriver.h"
#include "interrupts.h"
#include <naiveLegacy/naiveClock.h>
#include <naiveLegacy/naiveConsole.h>



// Process Control Block
	

#define MAXPROCESSES 256
#define PROCESSSTACKSIZE 4096

static int PIDCounter = 0;
static int activeProcess = -1;


int rand(){return getSeconds();}

static PCB processes[MAXPROCESSES]; 


int chooseNextProcess(int ap[], int n) {
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
	activeProcess = chooseNextProcess(ap, n);;
	return processes[activeProcess].stackAddress;
}




void * schedulet(void * oldStack) {


	int n,i,j,k,temp=65,flag=0;
	char process[20];
	int brust[20],priority[20],pos;
	int time=0,quantom=1,tbt=0;
	int z=0,lottery[20],ticket[20][20],q=0;
	//number of processes
	n=2;

	for(i=0;i<n;i++)
	{
		process[i] = temp;
		temp+=1;
	}
	for(i=0;i<n;i++)
	{
		brust[i] = rand();
		priority[i] = processes[i].priority;
	}
	
	//sorting burst time, priority and process number in ascending order using selection sort
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(priority[j]<priority[pos])
                pos=j;
        }
 
        temp=process[i];
        process[i]=process[pos];
        process[pos]=temp;
 
        temp=brust[i];
        brust[i]=brust[pos];
        brust[pos]=temp;
 
        temp=priority[i];
        priority[i]=priority[pos];
        priority[pos]=temp;
        
    }
    
	//assign one or more lottery numbers to each process
	int p=1,m_ticket=0;
	for(i=0;i<n;i++)
	{
		lottery[i]=(n-priority[i])+1;
		printWhiteString("el lottery[i]");
		printUint(lottery[i]);
		nextLine();
		for (z=0;z<lottery[i];z++) 
		{

            ticket[i][z] = p++;
            m_ticket = p;
        }
	}
	
	int winner = (rand()%m_ticket-1)+ 1;
	nextLine();
	printUint(winner);
	nextLine();
	

	//return processes[0].stackAddress;
	return  processes[winner].stackAddress;
}

// Returns pid?
uint8_t addProcess(void * entryPoint , uint64_t priority , char name , uint8_t foreground , uint64_t size){
	struct PCB newPCB;
	void * newStack = requestMemorySpace(PROCESSSTACKSIZE);
	newPCB.stackAddress = newStack;
	fillStackFrame (newPCB,entryPoint);
	newPCB.pid = PIDCounter;
	newPCB.status = PCB_READY;
	newPCB.priority = priority;
	newPCB.name = name;
	newPCB.foreground = foreground;
	newPCB.size = size;
	processes[PIDCounter] = newPCB;
	PIDCounter++;
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
	for (i = 0; i < PIDCounter; ++i)
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





