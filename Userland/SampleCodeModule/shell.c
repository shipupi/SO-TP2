#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
#include "memory.h"

void shell_init() {
	//Start Shell
	static char buffer[MAX_COMMAND_LENGTH];
	static char command[MAX_COMMAND_LENGTH];
	static char arguments[MAX_COMMAND_LENGTH];
	
	int background = 0;
	int exit = 0;
	printf("\nARQ TPE Group 2");
	printf("\nWhat module would you like to execute? (try 'help')");

	while (!exit) {
		memclear(command, MAX_COMMAND_LENGTH);
		memclear(arguments, MAX_COMMAND_LENGTH);
		printf("\n$>");
		scanf(buffer, MAX_COMMAND_LENGTH);
		int length = strlen(buffer);
		int i;
		int found = 0;
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
			printf("background\n");
		}
		exit = shell_execute(command,background, arguments);
	}
	printf("\nGoodbye.");
	return;
}

int shell_execute(char *command,int background, char *arguments) {
	int exit = 0;
	int l = strlen(arguments);
	printf("\n");
	//Now we need to compare the command to all the possible options
	if (strcmp(command, "help") == 0 || strcmp(command, "&help") == 0 ){
		//background == 0 ? help() : /*?*/ ;
		help();
	} 
	else if (strcmp(command, "time") == 0 || strcmp(command, "&time") == 0){
		//background == 0 ? showTime() : /*?*/ ;
		showTime();
	} 
	else if (strcmp(command, "pong") == 0 || strcmp(command, "&pong") == 0) {
		//background == 0 ? pong() : /*?*/ ;
		pong();
	} 
	else if (strcmp(command, "numbers") == 0 || strcmp(command, "&numbers") == 0) {
		if (background)
		{
			os_addProcess(&printNumbers,1,'c',1,4000);
		} else {
			printNumbers();
		}
	} 
	else if (strcmp(command, "exceptionDiv") == 0 || strcmp(command, "&exceptionDiv") == 0) {
		//background == 0 ? exceptioDiv0 : /*?*/ ;
		exceptionDiv0();
	} 
	else if (strcmp(command, "exceptionInvalidOp") == 0 || strcmp(command, "&exceptionInvalidOp") == 0 ) {
		//background == 0 ? exceptionInvalidOp() : /*?*/ ;
		exceptionInvalidOp();
	} 
	else if (strcmp(command, "clear") == 0 || strcmp(command, "&clear") == 0) {
		//background == 0 ? clear() : /*?*/ ;
		clear();
	} 
	else if (strcmp(command, "prodCons") == 0 || strcmp(command, "&prodCons") == 0) {
		//background == 0 ? exit() : /*?*/ ;
		//exit();
	} 
	else if (strcmp(command, "ps") == 0 || strcmp(command, "&ps") == 0) {
		//background == 0 ? ps() : /*?*/ ;
		ps();
	}
	else if (strcmp(command, "testMemoryManager") == 0 || strcmp(command, "&testMemoryManager") == 0) {
		//background == 0 ? testMemoryManager() : /*?*/ ;
		testMemoryManager();
	}
	else if (strcmp(command, "testScheduler") == 0 || strcmp(command, "&testScheduler") == 0) {
		//testScheduler();
	}
	else if (strcmp(command, "test") == 0 || strcmp(command, "&test") == 0) {
		os_sleepPID(2);
	}
	else if (strcmp(command, "test2") == 0 || strcmp(command, "&test2") == 0) {
		os_wakePID(2);
	}else if (strcmp(command, "sleep") == 0 || strcmp(command, "&sleep") == 0) {
		if(l !=0){
			int n = to_num(arguments,strlen(arguments));
			printf("Sleep: ");
			puint(n);
			printf("\n");
			sleepPID(n);
		}else{
			sleep();
		}
	}
	else if (strcmp(command, "wake") == 0 || strcmp(command, "&wake") == 0){
		if(l !=0){
			int n = to_num(arguments,l);
			wakePID(n);
		}else{
			printf("Error, argument needed");
		}
	}
	else {
		printf("\nshell: ");
		printf(command);
		printf(": command not found (try help)");
	}

	return exit;
}




