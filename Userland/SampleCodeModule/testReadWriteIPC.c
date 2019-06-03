#include "shell.h"
#include "modules.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
#include "PCB.h"

void testReadWriteIPC(){
	printf("\ntestIPC\n");
	
	os_ipc_create("uno",10);
	os_ipc_create("dos",20);
	os_ipc_create("tre",30);
	os_ipc_create("cua",40);
	os_ipc_create("baj",50);

	//todo probar crear cosas q ya existen 

	//todo probar que pasa si escribo mas de lo q entra

	os_ipc_write("baj","Bajan Cerati Spinetta",55);

	char msg[55];
	msg[0] = '1';
	msg[1] = 0;

	os_ipc_list();

	os_ipc_read("baj",msg,55);

	printf(msg);

	os_ipc_list();
}


void testReadWriteIPC2(){
	PCB* p = os_requestMemorySpace(sizeof(PCB));
	os_pstat(p);
	if (p->foreground == PCB_FOREGROUND)
	{
		printf("This application can only be run on the background\n");
		return;
	}
	os_freeMemorySpace(p, sizeof(PCB));


	char msg[55];
	msg[0] = '1';
	msg[1] = 0;
	os_ipc_create("baj",3);
	while(1) {
		os_ipc_read("baj",msg,55);
		printf(msg);
	}

}

void testReadWriteIPC3() {
	os_ipc_create("baj",3);	
	os_ipc_write("baj","Bajan Cerati Spinetta",55);
}