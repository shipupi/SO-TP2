#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <stdint.h>

void initializeMemoryManager();
void * requestMemorySpace(uint64_t requestedSpace);
void freeMemorySpace (void * freeBaseAddress,int32_t size);
#endif