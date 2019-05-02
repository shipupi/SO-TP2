#ifndef PCB_H
#define PCB_H

#include <stdint.h>


#define PCB_READY 0
#define PCB_LOCK 1
#define PCB_ENDED 2

typedef struct PCB {
	uint64_t pid;
	void * stackAddress;
	uint64_t status;
} PCB;

#endif