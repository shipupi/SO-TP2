#include <stdint.h>
#include <string.h>
#include "include/kernel.h"
#include "include/vesaDriver.h"

void * getMemorySpace( int32_t pid, uint64_t requestedSpace);
void initializeMemoryManager();
void freeMemorySpace (int32_t pid, void * freeBaseAddress);

#define MAXBLOCKS 32768
#define BLOCKSIZE 4096
static byte blockStatus[MAXBLOCKS];
static void * baseAddress = 0x900000;
static uint64_t size = 0x8000000;//128Mb = 2ˆ7*2ˆ10 = 131072

void * getBlockById(int32_t N){
	return baseAddress + N * blocksSize ;
}

int32_t getIdByAdress(void * address){
	return (address - baseAddress) / blocksSize ;
}

int32_t getBlocksForSize(uint64_t requestedSize){
	return (requestedSize / blocksSize)+1;
}

void initializeMemoryManager(){
	for(int i = 0 ; i < MAXBLOCKS ; i++){
		blockStatus[i] = 0;
	}
}

void * requestMemorySpace(uint64_t requestedSpace){
	int32_t n = getBlocksForSize(requestedSpace); //me must find n contiguous 0's in an array
	void * ret = -1;
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
