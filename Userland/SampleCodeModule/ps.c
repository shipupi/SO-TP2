#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
int ps(){
	printf("\nPS");
	os_listProcesses();
	return 0;
}

