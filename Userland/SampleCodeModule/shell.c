#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
#include "memory.h"
#include "PCB.h"

static SHORTCUT shortcuts[MAX_SHORTCUTS];
static int programs;

int splitString(char * pars, char separetor, char out[20][20]){
		
		int i = 0;
		int j = 0;
		int k = 0;
		int avoid=0;
		int getit = 0;
		//fit it seareted by separetor
		for(i = 0 ; i < strlen(pars); i++){

			if(getit == 1 && pars[i] == separetor){
				avoid =0;
			}

			if (pars[i] == separetor && avoid != 0){
				out[j][k] = 0;
				k = 0;
				j++;
				getit = 1;
			}
			if(pars[i] != separetor){
				getit = 0;
				out[j][k]=pars[i];
				k++;
			}

			if(i !=0){
				avoid = 1;
			}

		}


		// finish out

		for (int a = j+1;a <20; a++ ){
			for (int b = 0; b<20; b++){
				out[a][b] = 0;
			}

		}


		return j;
	}


void shell_init() {
	//Start Shell
	programs = initializeShortcutsArray(shortcuts);
	static char buffer[MAX_COMMAND_LENGTH];
	static char rightpipe[MAX_COMMAND_LENGTH];
	static char leftpipe[MAX_COMMAND_LENGTH];	
	static char command[MAX_COMMAND_LENGTH];
	static char arguments[MAX_COMMAND_LENGTH];
	static char pipeado[20][20];
	static char parseado_left[20][20];
	static char parseado_raight[20][20];
	int background = 0;
	int exit = 0;
	printf("\nSO TPE Group 4");
	printf("\nWhat module would you like to execute? (try 'help')");

	while (!exit) {
		memclear(command, MAX_COMMAND_LENGTH);
		memclear(arguments, MAX_COMMAND_LENGTH);
		memclear(leftpipe, MAX_COMMAND_LENGTH);
		memclear(rightpipe, MAX_COMMAND_LENGTH);
		memclear(pipeado,20);
		memclear(parseado_left,20);
		memclear(parseado_raight,20);
		printf("\n$>");

		scanf(buffer, MAX_COMMAND_LENGTH);
		int length = strlen(buffer);
		int i;
		int found = 0;
		
		int foundpipe = 0;

		char space[] = " ";

		for(int a = 0; a < 19; a++){
			for(int b = 0; b < 19; b++){
				parseado_left[a][b] = 0;
				parseado_raight[a][b] = 0;
				pipeado[a][b] = 0;
			}
		}
		
		
		char * left;
		char * raight;
		
		int pip = splitString(buffer,'!', pipeado);
		if(pip>0){
			left= pipeado[0];
			raight= pipeado[1];
			foundpipe = 1;
		}

		
		int argumentos_left = splitString(left, ' ', parseado_left);
		argumentos_left ++;
		

		
		int argumentos_raight = splitString(raight,' ',parseado_raight);
		argumentos_raight++;
		
		int aumento = 0;

		if (foundpipe) {
			
			//Creamos un pipe
			os_pipe_create("hola");

			//Ejecutamos producer y le ponemos como fdOut el pipe creado
			memcopy((void *) (uintptr_t) command, parseado_left[0], strlen(parseado_left[0]));
			command[strlen(parseado_left[0])+1] = 0;

			for(i =1; i<argumentos_left; i++){
				memcopy((void *) (uintptr_t) arguments + aumento, parseado_left[i], strlen(parseado_left[i]));
				memcopy((void *) (uintptr_t) arguments + aumento + strlen(parseado_left[i]), space, 1);
				aumento++;
					
				arguments[aumento + strlen(parseado_left[i])+1] = 0;
				aumento += strlen(parseado_left[i]);

			}
			//foundright = 1;
		
			printf("\n");
			printf("Ejecutamos producer: ");
			printf(command);
			//prntUint(space_index1);
			printf(" con parametros: ");
			printf(arguments);
			printf("\n");


			shell_execute(command,background,arguments, DEFAULT_FDIN, "hola");
			memclear(command, MAX_COMMAND_LENGTH);
			memclear(arguments, MAX_COMMAND_LENGTH);


			memcopy((void *) (uintptr_t) command, parseado_raight[0], strlen(parseado_raight[0]) );
			command[strlen(parseado_raight[0])] = 0;
			//printf(command); 
			aumento = 0;
			for(i =1; i<argumentos_raight; i++){
				memcopy((void *) (uintptr_t) arguments + aumento, parseado_raight[i], strlen(parseado_raight[i]));
				memcopy((void *) (uintptr_t) arguments + aumento + strlen(parseado_raight[i]), space, 1);
				aumento++;
				arguments[aumento + strlen(parseado_raight[i])+1] = 0;
				aumento += strlen(parseado_raight[i]);
			}
			



			printf("Ejecutamos consumer: ");
			printf(command);
			printf(" con parametros: ");
			printf(arguments);
			printf("\n");
			shell_execute(command,background,arguments, "hola", DEFAULT_FDOUT);
		} else {
			for (i = 0; i < length; ++i)
			{
				if (buffer[i] == ' ' && i != length-1) {
					memcopy((void *) (uintptr_t) command, buffer, i);
					command[i+1] = 0;
					memcopy((void *) (uintptr_t) arguments, buffer + i + 1, length - i - 1);
					arguments[length -i] = 0;
					found = 1;
					break;
				}
			}

			if (!found)
			{
				memcopy((void *) (uintptr_t) command, buffer, length);
				arguments[0] = 0;
			}

			if(command[0] == '&'){
				background = 1;
			}
			exit = shell_execute(command,background, arguments, DEFAULT_FDIN, DEFAULT_FDOUT);
		}
	}
	printf("\nGoodbye.");
	return;
}

int shell_execute(char *command,int background, char *arguments, char * fdIn, char * fdOut) {
	int exit = 0;
	printf("\n");
	int found = -1;
	int bg = command[0] == '&'? 1: 0;
	for (int i = 0; i < programs; ++i)
	{
		
		if (strcmp(bg?command+1: command, shortcuts[i].id) == 0)
		{
			found = i;
			break;
		} 
	}
	if (found != -1) {
		char * ptr = shortcuts[found].pointer;
		if (bg) {
			os_addProcess(ptr,1, PCB_BACKGROUND, 4000, fdIn, "SPLIT_FD");
		} else {
			((EntryPoint)(ptr))(arguments);
		}
	} else {
		printf("\nshell: ");
		printf(command);
		printf(": command not found (try help)");
	}

	return exit;
}

void addDefaultProcess(char * ptr, int priority, int background, int size) {
	os_addProcess(ptr, priority, background, size, DEFAULT_FDIN, DEFAULT_FDOUT);
}