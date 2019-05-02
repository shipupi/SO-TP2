#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"


void shell_init() {
	//Start Shell
	static char command[MAX_COMMAND_LENGTH];
	int exit = 0;
	printf("\nARQ TPE Group 2");
	printf("\nWhat module would you like to execute? (try 'help')");

    printf("\n");
	void * addr1 = os_requestMemorySpace(6000); // Request de 2 bloques (Deberia dar base Address = 0x900000
    printUint((uint64_t)(uintptr_t) addr1); // request de 1 bloque (Deberia imprimir 0x900000 + 4096 * 2)
    printf("\n");
    printUint((uint64_t)(uintptr_t) os_requestMemorySpace(50)); // request de 1 bloque (Deberia imprimir 0x900000 + 4096 * 2)
    printf("\n");
    os_freeMemorySpace (addr1,5000); // Libero los primeros 2 bloques
    printUint((uint64_t)(uintptr_t) os_requestMemorySpace(10000)); // request de 3 bloque (Deberia imprimir 0x900000 + 4096 * 3)
    printf("\n");
    printUint((uint64_t)(uintptr_t) os_requestMemorySpace(6000)); // request de 2 bloque (Deberia imprimir 0x900000)
	printf("\n");

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