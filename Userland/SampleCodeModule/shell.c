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
void shell_init() {
	//Start Shell
	programs = initializeShortcutsArray(shortcuts);
	static char buffer[MAX_COMMAND_LENGTH];
	static char rightpipe[MAX_COMMAND_LENGTH];
	static char leftpipe[MAX_COMMAND_LENGTH];	
	static char command[MAX_COMMAND_LENGTH];
	static char commandright[MAX_COMMAND_LENGTH];
	static char arguments[MAX_COMMAND_LENGTH];
	int background = 0;
	int exit = 0;
	printf("\nSO TPE Group 4");
	printf("\nWhat module would you like to execute? (try 'help')");

	while (!exit) {
		memclear(command, MAX_COMMAND_LENGTH);
		memclear(arguments, MAX_COMMAND_LENGTH);
		memclear(leftpipe, MAX_COMMAND_LENGTH);
		memclear(rightpipe, MAX_COMMAND_LENGTH);
		printf("\n$>");
		scanf(buffer, MAX_COMMAND_LENGTH);
		int length = strlen(buffer);
		int i,j;
		int found = 0;
		int foundleft = 0;
		int foundright = 0;
		int foundpipe = 0;
		int pipeindex=0;


		// busco pipes en el buffer
		for (i = 0; i< length; i++){
			if(buffer[i] == '!'){
				foundpipe = 1;
				pipeindex = i;
			}
		}


		if (foundpipe) {
			
			//Creamos un pipe

			//Ejecutamos producer y le ponemos como fdOut el pipe creado
			memcopy((void *) (uintptr_t) command, buffer, pipeindex - 1);
			command[i+1] = 0;
			//memcopy((void *) (uintptr_t) arguments, pipeindex + 2, length - i - 1);
			//arguments[length -i] = 0;
			//foundright = 1;
		
			printf("\n");
			printf("Ejecutamos producer: ");
			printf(command);
			printf(" con parametros: ");
			printf(arguments);
			printf("\n");

			// Ejecutamos consumer y le ponemos como FdInt el pipe creado
			for (i = pipeindex, j = 0 ; i <length && foundpipe == 1 ; i++, j++){
				rightpipe[j] = buffer[i];
				//copio y pego la forma de llamar 
				if (buffer[i] == ' ' && i != length-1) {
					memcopy((void *) (uintptr_t) commandright, rightpipe, i);
					command[i+1] = 0;
					memcopy((void *) (uintptr_t) arguments, rightpipe + i + 1, length - i - 1);
					arguments[length -i] = 0;
					foundleft = 1;
					break;
				}	
			}


			printf("Ejecutamos consumer: ");
			printf(command);
			printf(" con parametros: ");
			printf(arguments);
			printf("\n");
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
			exit = shell_execute(command,background, arguments);
		}
	}
	printf("\nGoodbye.");
	return;
}

int shell_execute(char *command,int background, char *arguments) {
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
			addDefaultProcess(ptr,1,PCB_BACKGROUND,4000);
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