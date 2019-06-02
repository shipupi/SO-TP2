#include "include/shell.h"
#include "include/modules.h"
#include "include/string.h"
#include "include/stdio.h"
#include "include/syscalls.h"
#include "include/applications.h"
//#include "utils.h"


void changePriority(char * args){
	printf("\nArgumentos:");
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
	

	char parse[20][20];
	for(int a = 0; a< 20; a++){
		for(int b = 0; b <20; b++){
			parse[a][b]= 0;
		}
	}
	splitString(args,' ',parse);
	int arg1 = to_num(parse[0],strlen(parse[0]));
	int arg2 = to_num(parse[1],strlen(parse[1]));

	os_change_priority(arg1,arg2);
	printf("Llama a ps para testear q ande\n");
	return ;
}


