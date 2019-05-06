#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
int ticks(){
	printf("\nticks");
	return os_ticks();
}




