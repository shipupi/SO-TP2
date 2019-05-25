#include <stdint.h>
#include "memoryManager/memoryManager.h"
#include "include/lib.h"
#include "ipc/ipc.h"
#include "ipc/mutex.h"
#include "include/string.h"
#include "include/drivers/vesaDriver.h"
#include "include/interrupts.h"
#include "include/ipc/changePriority.h"

void changePriority(uint64_t pid , int priority){
	printWhiteString("	");
	printWhiteString("changePriority");
	printWhiteString("	");
	return;
}



