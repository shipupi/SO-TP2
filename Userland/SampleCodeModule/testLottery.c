
#include "syscalls.h"
#include "applications.h"

void testLottery() {
	os_addProcess(&printNumbers1,1,'c',1,4000);
	os_addProcess(&printNumbers2,5,'c',1,4000);
}