#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
void pipe(){
	printf("\nPIPE\n");
	printf("Testeando las funciones de pipe\n");
	os_pipe_create("abc");
	os_pipe_delete("abc");
	//os_pipe_read("abc","aaa",12);
	//os_pipe_write("abc","aaa",12);
	return ;
}




