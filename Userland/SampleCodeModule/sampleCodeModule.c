/* sampleCodeModule.c */
#include "include/shell.h"
#include "include/syscalls.h"
#include "include/stdio.h"

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	//printWhiteString("Probando...");
	//We call the init of Shell
	// printUint(&shell_init);
	char name = 'A';
	os_addProcess(&shell_init,1,name,1,50);
	os_addProcess(&shell_init,2,name,1,50);
	os_addProcess(&shell_init,3,name,1,50);
	os_endProcess(1);
	os_endProcess(2);
	os_addProcess(&shell_init,4,name,1,50);
	//os_listProcesses();
	shell_init();
	return 1;
}


