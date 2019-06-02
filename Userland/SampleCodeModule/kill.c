#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
void kill(char * param){

	char parse[20][20];
	splitString(param,' ',parse);
	printf("param");
	int arg = to_num(parse[0], strlen(parse[0]));
	printf("\nkill");
	printf("\n");
	
	pint(arg);
	
}
