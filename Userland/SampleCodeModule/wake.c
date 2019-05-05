#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
void wake(){
	printf("\nWAKE");
	os_sleep();
}

void wakePID(int pid){
	printf("\nWAKEPID");
	os_sleep();
}