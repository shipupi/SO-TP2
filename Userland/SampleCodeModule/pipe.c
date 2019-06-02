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
	uint64_t a = 0;
	int b = 0;
	while(1) {
		a++;
		if(a % 1000001 == 0) {

			// b++;
			printf("2");
			// puint(a % 10);
			// pint(5);
		}
		// if(b == 5) return;
	}
}

void read2() {
	// PCB* p = os_requestMemorySpace(sizeof(PCB));
	// os_pstat(p);
	// if (p->foreground == PCB_FOREGROUND)
	// {
	// 	printf("This application can only be run on the background\n");
	// 	return;
	// }
	// os_freeMemorySpace(p, sizeof(PCB));

	//read 2
	char c;
	while(1) {
		// os_listProcesses();
		c = getChar();
		pint((c - '0') * 2);
	}
}