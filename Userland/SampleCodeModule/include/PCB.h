#ifndef UPCB_H
#define UPCB_H

#include <stdint.h>


#define PCB_READY 3
#define PCB_LOCK 1
#define PCB_ENDED 2

#define PCB_FOREGROUND 1
#define PCB_BACKGROUND 2

typedef struct PCB {
	uint64_t pid;
	void * stackAddress;
	void * baseAddress;
	uint64_t status;
	uint64_t priority;
	char name;
	uint8_t foreground;
	uint64_t size;
} PCB;

#endif