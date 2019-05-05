#ifndef SHELL_H
#define SHELL_H

//Change this numner to whatever you feel like
#define MAX_COMMAND_LENGTH 1024

void shell_init();
int shell_execute(char *command,char background);

#endif