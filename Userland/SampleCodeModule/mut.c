#include "include/stdio.h"
#include "include/syscalls.h"

void list_mutex() {
	os_mut_list();
}

void mut1() {
	os_mut_create("test");
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