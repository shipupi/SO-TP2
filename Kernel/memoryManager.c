#include <stdint.h>
#include <string.h>
#include "include/kernel.h"
#include "include/vesaDriver.h"

void *getMemorySpace( int32_t pid, uint64_t requestedSpace);
void initializeMemoryManager();
void freeMemorySpace (int32_t pid, void * freeBaseAddress);

extern uint8_t endOfKernel;
#define MAXBLOCKS 50
static uint64_t blocksSize[MAXBLOCKS];
static void * blocksAddress[MAXBLOCKS];
static int32_t blocksPid[MAXBLOCKS];
static uint64_t activeBlocks;

void numberToString(uint64_t number, char * string) {
	int i = 0;
	while(number > 10) {
		string[i] = (number % 10) + '0';
		number = number / 10;
		i++;
	}
}


void initializeMemoryManager() {
	void * baseAddress = getStackBase();
	uint64_t size = (uint64_t) &endOfKernel - (uint64_t) baseAddress;

	// Initialize first block
	// Size = total size
	// Address = BaseAddress
	// Process = -1 (unassigned)
	activeBlocks = 1;
	blocksSize[0] = size;
	blocksAddress[0] = baseAddress;
	blocksPid[0] = -1;
}

void * requestMemorySpace ( int32_t pid, uint64_t requestedSpace) {

	// First fit algorithm
	int i;
	int assignedBlock = -1;
	for (i = 0; i < activeBlocks; ++i)
	{
		// If block is unassigned, and block has available space. assign
		if (blocksPid[i] == -1 && blocksSize[i] >= requestedSpace) {
			assignedBlock = i;
			break;
		}
	}
	// End of algorithm

	if (assignedBlock == -1)
	{
		// No found blocks, throw error?
	} else {
		// Assign the block
		blocksPid[assignedBlock] = pid;
		if (requestedSpace > blocksSize[assignedBlock])
		{
			// We have leftover space. Lets assign it to a new block
			// Active blocks is the index of the new created block
			blocksPid[activeBlocks] = -1;
			blocksAddress[activeBlocks] = blocksAddress[assignedBlock] + requestedSpace + 1;
			blocksSize[activeBlocks] = blocksSize[assignedBlock] - requestedSpace;
			activeBlocks++; 
		}
	}

	return blocksAddress[assignedBlock];
}

void freeMemorySpace (int32_t pid, void * freeBaseAddress) {
	int i = 0;
	int block = -1;
	for (i = 0; i < activeBlocks; ++i)
	{
		if (blocksAddress[i] == freeBaseAddress)
		{
			block = i;
			break;
		}
	}

	if (block == -1) {
		// Requested to release unassigned block, throw error?
	} else {
		// Check if block is assigned to requested pid
		if (blocksPid[block] == pid) {
			// Free the block
			// Merge with adjacent free blocks? how do we do that?
			// Next one should be easy, previous one is harder, maybe keep a pointer to the previous block?
			blocksPid[block] = -1;
		} else {
			// Free request not made by block owner, throw error?
		}
	}

}