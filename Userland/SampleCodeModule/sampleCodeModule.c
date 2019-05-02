/* sampleCodeModule.c */
#include "include/shell.h"
#include "include/syscalls.h"
#include "include/stdio.h"

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	//We call the init of Shell
	// printUint(&shell_init);
	os_addProcess(&shell_init);
	// os_listProcesses();
	// shell_init();
}