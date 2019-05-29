#ifndef PCB_H
#define PCB_H

#include <stdint.h>


#define PCB_READY 3
#define PCB_LOCK 1
#define PCB_ENDED 2

#define DEFAULT_FDIN "KEYBOARD_IPC"
#define DEFAULT_FDOUT "SCREEN_IPC"
#define MAXFDSIZE 255
#define PCB_FOREGROUND 1
#define PCB_BACKGROUND 2

typedef struct PCB {
	uint64_t pid;
	void * stackAddress;
	void * baseAddress;
	uint64_t status;
	uint64_t priority;
	uint8_t foreground;
	uint64_t size;
	char fdIn[MAXFDSIZE];
	char fdOut[MAXFDSIZE];
} PCB;

#endif