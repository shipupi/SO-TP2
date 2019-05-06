#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"

void testReadWriteIPC(){
	printf("\ntestIPC\n");
	
	os_ipc_create("uno",10);
	os_ipc_create("dos",20);
	os_ipc_create("tres",30);
	os_ipc_create("cuatro",40);
	os_ipc_create("bajan",50);

	//todo probar crear cosas q ya existen 

	//todo probar que pasa si escribo mas de lo q entra

	os_ipc_write("bajan","Bajan Cerati Spinetta",55);

	char msg[55];

	os_ipc_read("bajan",msg,55);

	printf(msg);

	os_ipc_list();
}




