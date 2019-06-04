
#include "syscalls.h"
#include "applications.h"
#include "include/pcb.h"

void testLottery() {
	os_addProcess(&printNumbers1,1,1,4000,DEFAULT_FDIN,DEFAULT_FDOUT);
	os_addProcess(&printNumbers2,5,1,4000,DEFAULT_FDIN,DEFAULT_FDOUT);
}

