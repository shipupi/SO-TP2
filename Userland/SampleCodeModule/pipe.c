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

			b++;
			// printf("2");
			puint(a % 10);
			// pint(5);
		}
		// if(b == 5) return;
	}
}

void read2() {
	char c;
	// char str[2] = {0,0};
	while(1) {
		c = getChar();
		pint((c - '0') * 2);
	}
}