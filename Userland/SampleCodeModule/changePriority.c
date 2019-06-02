#include "include/shell.h"
#include "include/modules.h"
#include "include/string.h"
#include "include/stdio.h"
#include "include/syscalls.h"
#include "include/applications.h"
//#include "utils.h"
void changePriority(char * args){
	printf("\nArgumentos: ");
	printf(args);
	printf("\nCHPR\n");
	printf("Testeando las funciones de CHPR\n");
	
	//Chequear que se parseen bien los paramtetros
	int i;
	// int flag = 0;
	// int counter = 0;
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


