#include "include/stdio.h"
#include "include/syscalls.h"
#include "include/PCB.h"


void list_mutex() {
	os_mut_list();
}

void mut1() {
	PCB p;
	os_pstat(&p);
	if (p.foreground == PCB_FOREGROUND)
	{
		printf("This application can only be run on the background\n");
		return;
	}

	os_mut_create("test");
	os_mut_list();
	while(1) {
		os_mut_request("test");
		printf("\nTengo turno!\n");
	}
}

void mut2() {
	os_mut_create("test");
	os_mut_release("test");
	return;
}