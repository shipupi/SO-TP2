#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "include/lib.h"
#include "ipc/ipc.h"
#include "ipc/mutex.h"
#include "include/string.h"
#include "include/drivers/vesaDriver.h"
#include "include/interrupts.h"
#include "include/ipc/pipe.h"

void pipe_create(char * pipeid){
	printWhiteString(pipeid);
	printWhiteString("	");
	printWhiteString("PIPECREATE");
	printWhiteString("	");
	return;
}

void pipe_delete(char * pipeid){
	printWhiteString(pipeid);
	printWhiteString("	");
	printWhiteString("PIPEDELETE");
	printWhiteString("	");
	return;
}

void pipe_read(char * pipeid , char * buffer , int messageSize){
	printWhiteString(pipeid);
	printWhiteString("	");
	printWhiteString(buffer);
	printWhiteString("	");
	printWhiteString("PIPEREAD");
	printWhiteString("	");
	return;
}

void pipe_write(char * pipeid , char * buffer , int messageSize){
	printWhiteString(pipeid);
	printWhiteString("	");
	printWhiteString(buffer);
	printWhiteString("	");
	printWhiteString("PIPEWRITE");
	printWhiteString("	");
	return;
}




