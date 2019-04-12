#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"


void shell_init() {
	//Start Shell
	static char command[MAX_COMMAND_LENGTH];
	int exit = 0;
	printf("\nARQ TPE Group 2");
	printf("\nWhat module would you like to execute? (try 'help')");
	while (!exit) {
		printf("\n$>");
		scanf(command, MAX_COMMAND_LENGTH);
		exit = shell_execute(command);
	}
	printf("\nGoodbye.");
	return;
}

int shell_execute(char *command) {
	int exit = 0;

	//Now we need to compare the command to all the possible options
	if (strcmp(command, "help") == 0) {
		help();
		return exit;
	} else if (strcmp(command, "time") == 0) {
		showTime();
		return exit;
	} else if (strcmp(command, "pong") == 0) {
		pong();
		return exit;
	} else if (strcmp(command, "exceptionDiv") == 0) {
		exceptionDiv0();
		return exit;
	} else if (strcmp(command, "exceptionInvalidOp") == 0) {
		exceptionInvalidOp();
		return exit;
	} else if (strcmp(command, "clear") == 0) {
		clear();
		return exit;
	} else if (strcmp(command, "exit") == 0) {
		exit = 1;
		return exit;
	} else {
		printf("\nshell: ");
		printf(command);
		printf(": command not found (try help)");
		return exit;
	}
}