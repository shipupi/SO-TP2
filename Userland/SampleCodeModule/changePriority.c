#include "include/shell.h"
#include "include/modules.h"
#include "include/string.h"
#include "include/stdio.h"
#include "include/syscalls.h"
#include "include/applications.h"
//#include "utils.h"

#define INITIAL 0
#define SEP 1
#define LETTER 2

int splitString2(char * pars, char separetor, char out[20][20]){

	int state = INITIAL;
	int j = 0;
	int k = 0;
	for(int i = 0; i< strlen(pars); i++){
		switch(state){

		case INITIAL:
				if(pars[i] == separetor){
					state = SEP;
				}else{
					out[j][k] = pars[i];
					k++;
					state = LETTER;
				}
			break;
		case SEP:
			if(pars[i] == separetor){
				state = SEP;
			}else{
				out[j][k] = pars[i];
				k++;
				state = LETTER;
			}

			break;
		case LETTER:
			if(pars[i] == separetor){
				out[j][k++]= 0;
				j++;
				k=0;
				state = SEP;

			}else{
				out[j][k] = pars[i];
				k++;
			}

			break;
		}
	}
		
	}


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
	splitString2(args,' ',parse);
	int arg1 = to_num(parse[0],1);
	int arg2 = to_num(parse[1],1);

	printf(" ");
	printf(parse[0]);
	printf(" ");
	printf(parse[1]);
	printf(" ");
	
	


	pint(arg1);
	printf(" ");
	//puint(arg2);
	printf(" ");

	os_change_priority(arg1,arg2);
	printf("Llama a ps para testear q ande\n");
	return ;
}


