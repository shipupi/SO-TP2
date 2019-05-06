#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"

void testIPC(){
	printf("\ntestIPC\n");
	
	os_ipc_create("uno",10);
	os_ipc_create("dos",20);
	os_ipc_create("tres",30);
	os_ipc_create("cuatro",40);
	os_ipc_create("uno",10);
	os_ipc_create("dos",20);
	os_ipc_create("tres",30);
	os_ipc_create("uno",10);
	os_ipc_create("dos",20);
	os_ipc_create("tres",30);

	
	os_ipc_list();
}


