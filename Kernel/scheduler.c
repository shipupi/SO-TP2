#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "scheduler/PCB.h"
#include "drivers/vesaDriver.h"
#include <naiveLegacy/naiveClock.h>
#include <naiveLegacy/naiveConsole.h>



// Process Control Block
	

#define MAXPROCESSES 256
#define PROCESSSTACKSIZE 4096

static int currentPID = 0;


static PCB processes[MAXPROCESSES]; 

int rand(){
	return getSeconds();
}

void * schedule(void * oldStack) {
	int n,i,j,k,temp=65,flag=0;
	char process[20];
	int brust[20],priority[20],pos;
	int time=0,quantom=1,tbt=0;
	int z=0,lottery[20],ticket[20][20],q=0;
	//number of processes
	n=3;

	for(i=0;i<n;i++)
	{
		process[i] = temp;
		temp+=1;
	}
	for(i=0;i<n;i++)
	{
		brust[i] = 2;
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
		lottery[i] = (brust[i]/quantom) + (n-priority[i]);
		for (z=0;z<lottery[i];z++) 
		{
            ticket[i][z] = p++;
            m_ticket = p;
        }
	}
	
	int winner = (rand()%m_ticket-1)+ 1;

	return  processes[winner].stackAddress;

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




