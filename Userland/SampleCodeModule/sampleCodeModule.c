/* sampleCodeModule.c */
#include "include/shell.h"
#include "include/syscalls.h"
#include "include/stdio.h"

// char * v = (char*)0xB8000 + 79 * 2;

int main() {
	//printWhiteString("Probando...");
	//We call the init of Shell
	// printUint(&shell_init);
	// char name = 'A';
	os_addProcess(&shell_init,1,'c',1,50);
	// os_addProcess(&shell_init,2,name,1,50);
	// os_addProcess(&shell_init,3,name,1,50);
	// os_endProcess(1);
	// os_endProcess(2);
	//os_addProcess(&shell_init,4,name,1,50);
	os_listProcesses();
	// shell_init();
	int a = 0;
	int b= 0;
	// while(1) {
	// 	// Llamar a halt?
	// 	// o a sleep
	// }
	while(1) {
		a++;
		if (a%25000000 == 0)
		{
			b++;
			puint(b);
		}
	}
	return 1;
}


