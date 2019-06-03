#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <stdint.h>


#define MAXBLOCKS 32768
#define BLOCKSIZE 4096
#define BLOCKSPOWER 15
#define BASEADDRESS 0x9000000
#define NODE_FULL 2
#define NODE_PARTIAL 1
#define NODE_EMPTY 0

void initializeMemoryManager();
void * requestMemorySpace(uint64_t requestedSpace);
void freeMemorySpace (void * freeBaseAddress,int32_t size);
#endif