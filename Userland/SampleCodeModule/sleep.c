#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
void sleep(){
	printf("\nSLEEP");
	os_sleep();
}

void sleepPID(int pid){
	printf("\nSLEEPPID");
	os_sleep();
}