/* sampleCodeModule.c */
#include "include/shell.h"
#include "include/syscalls.h"
#include "include/stdio.h"
#include "include/PCB.h"

// char * v = (char*)0xB8000 + 79 * 2;

int main() {
	//printWhiteString("Probando...");
	//We call the init of Shell
	// printUint(&shell_init);
	// char name = 'A';
	//os_pipe_create("crando pipe");
	os_addProcess(&shell_init,1,PCB_FOREGROUND,50,"","");
	// os_addProcess(&shell_init,2,name,1,50);
	// os_addProcess(&shell_init,3,name,1,50);
	// os_endProcess(1);
	// os_endProcess(2);
	//os_addProcess(&shell_init,4,name,1,50);
	//shell_init();
	// os_sleep();
	os_endProcess(os_pid());
	while(1) {} // while 1 hasta q Programa finalizado
	return 1;
}




