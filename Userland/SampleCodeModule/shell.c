#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"


void shell_init() {
	//Start Shell
	static char command[MAX_COMMAND_LENGTH];
	char background = 0;
	int exit = 0;
	printf("\nARQ TPE Group 2");
	printf("\nWhat module would you like to execute? (try 'help')");

	while (!exit) {
		printf("\n$>");
		scanf(command, MAX_COMMAND_LENGTH);
		if(command[0]=="&"){
			background = 1;
			printf("background\n");
		}
		exit = shell_execute(command,background);
	}
	printf("\nGoodbye.");
	return;
}

int shell_execute(char *command,char background) {
	int exit = 0;

	//Now we need to compare the command to all the possible options
	if (strcmp(command, "help") == 0 || strcmp(command, "&help") == 0 ){
		//background == 0 ? help() : /*?*/ ;
		help();
		return exit;
	} 
	else if (strcmp(command, "time") == 0 || strcmp(command, "&time") == 0){
		//background == 0 ? showTime() : /*?*/ ;
		showTime();
		return exit;
	} 
	else if (strcmp(command, "pong") == 0 || strcmp(command, "&pong") == 0) {
		//background == 0 ? pong() : /*?*/ ;
		pong();
		return exit;
	} 
	else if (strcmp(command, "exceptionDiv") == 0 || strcmp(command, "&exceptionDiv") == 0) {
		//background == 0 ? exceptioDiv0 : /*?*/ ;
		exceptionDiv0();
		return exit;
	} 
	else if (strcmp(command, "exceptionInvalidOp") == 0 || strcmp(command, "&exceptionInvalidOp") == 0 ) {
		//background == 0 ? exceptionInvalidOp() : /*?*/ ;
		exceptionInvalidOp();
		return exit;
	} 
	else if (strcmp(command, "clear") == 0 || strcmp(command, "&clear") == 0) {
		//background == 0 ? clear() : /*?*/ ;
		clear();
		return exit;
	} 
	else if (strcmp(command, "prodCons") == 0 || strcmp(command, "&prodCons") == 0) {
		//background == 0 ? exit() : /*?*/ ;
		//exit();
		return exit;
	} 
	else if (strcmp(command, "ps") == 0 || strcmp(command, "&ps") == 0) {
		//background == 0 ? ps() : /*?*/ ;
		ps();
		return exit;
	}
	else if (strcmp(command, "testMemoryManager") == 0 || strcmp(command, "&testMemoryManager") == 0) {
		//background == 0 ? testMemoryManager() : /*?*/ ;
		testMemoryManager();
		return exit;
	}
	else if (strcmp(command, "testScheduler") == 0 || strcmp(command, "&testScheduler") == 0) {
		//testScheduler();
		return exit;
	}
	else if (strcmp(command, "exit") == 0 || strcmp(command, "&exit") == 0) {
		exit = 1;
		return exit;
	} 
	else {
		printf("\nshell: ");
		printf(command);
		printf(": command not found (try help)");
		return exit;
	}
}


