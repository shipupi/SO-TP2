#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
void changePriority(char * args){
	printf("\nArgumentos: ");
	printf(args);
	printf("\nCHPR\n");
	printf("Testeando las funciones de CHPR\n");
	//Chequear que se parseen bien los paramtetros
	os_change_priority(1,3);
	printf("Llama a ps para testear q ande\n");
	return ;
}
