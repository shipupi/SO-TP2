#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <stdint.h>

void initializeMemoryManager();
void * requestMemorySpace(uint64_t requestedSpace);
#endif