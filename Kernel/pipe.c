#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "include/lib.h"
#include "ipc/ipc.h"
#include "ipc/mutex.h"
#include "include/string.h"
#include "include/drivers/vesaDriver.h"
#include "include/interrupts.h"
#include "include/ipc/pipe.h"
#include "include/scheduler/PCB.h"

void pipe_create(char * pipeid){
	ipc_create(pipeid,MAXFDSIZE);
	return;
}

void pipe_delete(char * pipeid){
	// DELETE IPC (not implemented)
}

void pipe_read(char * pipeid , char * buffer , int messageSize){
	ipc_read(pipeid, buffer, messageSize);
	return;
}

void pipe_write(char * pipeid , char * buffer , int messageSize){
	ipc_write(pipeid, buffer, messageSize);
	return;
}