#include <stdint.h>
#include <string.h>
#include "include/kernel.h"
#include "include/vesaDriver.h"

void * getMemorySpace( int32_t pid, uint64_t requestedSpace);
void initializeMemoryManager();
void freeMemorySpace (void * freeBaseAddress,int32_t size);

#define MAXBLOCKS 32768
#define BLOCKSIZE 4096
static char blockStatus[MAXBLOCKS];
static void * baseAddress = (void *)(uintptr_t) 0x900000;

void * getBlockById(int32_t N){
	return baseAddress + N * BLOCKSIZE ;
}

int32_t getIdByAdress(void * address){
	return (address - baseAddress) / BLOCKSIZE ;
}

int32_t getBlocksForSize(uint64_t requestedSize){
	return (requestedSize / BLOCKSIZE)+1;
}

void initializeMemoryManager(){
	for(int i = 0 ; i < MAXBLOCKS ; i++){
		blockStatus[i] = 0;
	}
}

void * requestMemorySpace(uint64_t requestedSpace){
	int32_t n = getBlocksForSize(requestedSpace); //me must find n contiguous 0's in an array
	void * ret = (char *)(uintptr_t) -1;
	int32_t base = 0;

	int acum = 0;
	for(int i=0;i<MAXBLOCKS;i++){
		if(blockStatus[i]==0){
			if(acum==0){
				base = i;
			}
			acum++;
		}
		else if(blockStatus[i]==1){
			acum = 0;
		}

		if(acum==n){
			ret = getBlockById(base) ;
			break;
		}
	}

	return ret;
	}


void freeMemorySpace (void * freeBaseAddress,int32_t size){
	int32_t sz = getBlocksForSize(size);
	int32_t id = getIdByAdress(freeBaseAddress); 

	for(int i = id ; i < sz + id  ; i++){
		blockStatus[i] = 0;
	}

}
