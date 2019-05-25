#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
void pipe(){
	printf("\nPIPE");
	os_pipe_create("abc");
	return ;
}



