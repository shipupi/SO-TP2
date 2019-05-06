#include "include/exec.h"
#include "include/syscalls.h"
#include "include/stdio.h"
typedef int (*EntryPoint)();

void execv() {
	os_ipc_create("exec",10);

	int ptr_size = sizeof(void *);
	char program[ptr_size];
	os_ipc_read("exec", program, ptr_size);
	// ((EntryPoint) program)();
	// os_endProcess(os_pid());
	printf("\n exec: "); puint((uint64_t)(uintptr_t) *(program));
	printf("\n");
	// os_addProcess(program,1,'c',1,4000);
	return;
}