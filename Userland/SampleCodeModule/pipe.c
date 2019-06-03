#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
#include "PCB.h"
void pipe(){
	printf("\nPIPE\n");
	printf("Testeando las funciones de pipe\n");
	os_pipe_create("abc");
	os_pipe_delete("abc");
	os_pipe_read("abc","aaa",12);
	os_pipe_write("abc","aaa",12);
	return ;
}

void write2() {
	int b = 0;
	for (int i = 0; i < 20000; ++i)
	{
		printf("2");
	}
	// puint(a % 10);
	// pint(5);
	if(b == 100) return;
}

void read2() {
	PCB* p = os_requestMemorySpace(sizeof(PCB));
	os_pstat(p);
	if (p->foreground == PCB_FOREGROUND)
	{
		printf("This application can only be run on the background\n");
		return;
	}
	os_freeMemorySpace(p, sizeof(PCB));

	//read 2
	char c;
	printf(" ");
	while(1) {
		c = getChar();
		pint((c - '0') * 2);
	}
	return;
}