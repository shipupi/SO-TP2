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
	printWhiteString("	");
	printWhiteString(pipeid);
	printWhiteString("	");
	printWhiteString("Aca estoy");
	printWhiteString("	");
	return;
}

