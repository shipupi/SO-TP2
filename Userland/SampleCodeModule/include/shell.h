#ifndef SHELL_H
#define SHELL_H

//Change this numner to whatever you feel like
#define MAX_COMMAND_LENGTH 1024
#define MAX_SHORTCUTS 1024

#include <stdint.h>
void shell_init();
int shell_execute(char *command,int background, char *arguments);
int shell_bgexec(uintptr_t path);

typedef struct SHORTCUT {
	char id[MAX_COMMAND_LENGTH];
	char * pointer;
} SHORTCUT;
typedef int (*EntryPoint)();

#endif
