#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
void changePriority(){
	printf("\nCHPR\n");
	printf("Testeando las funciones de CHPR\n");
	os_change_priority(1,1);
	return ;
}


