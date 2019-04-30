/* sampleCodeModule.c */
#include "include/shell.h"

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	//We call the init of Shell
	shell_init();

	return 0;
}