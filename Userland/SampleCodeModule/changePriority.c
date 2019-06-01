#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
//#include "utils.h"
void changePriority(char * args){
	printf("\nArgumentos: ");
	printf(args);
	printf("\nCHPR\n");
	printf("Testeando las funciones de CHPR\n");
	
	//Chequear que se parseen bien los paramtetros
	int i;
	int flag = 0;
	int counter = 0;
	for(i = 0 ; args[i] !='\0' ; i++){
		if(args[i] != ' '){

		}
	}

	//scanf pid

	//scanf priority
	

	os_change_priority(1,3);
	printf("Llama a ps para testear q ande\n");
	return ;
}


