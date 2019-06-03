#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"

void kill(char * param){

	printf("param");
	int arg  = to_num(param, strlen(param));
	printf("\nkill");
	printf("\n");

	os_kill(arg);
	
	puint(arg);
	
}