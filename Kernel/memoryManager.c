#include <stdint.h>
#include "include/string.h"
#include "include/kernel.h"
#include "include/memoryManager/memoryManager.h"
#include "include/drivers/vesaDriver.h"


static char blockStatus[MAXBLOCKS];
static void * baseAddress = (void *)(uintptr_t) BASE_ADDRESS;

void * getBlockById(int32_t N){
	return baseAddress + N * BLOCKSIZE ;
}

int32_t getIdByAdress(void * address){
	return (address - baseAddress) / BLOCKSIZE ;
}

int32_t getBlocksForSize(uint64_t requestedSize){
	if (requestedSize == 0) {
		return 0;
	}
	return ((requestedSize - 1)/ BLOCKSIZE)+1;
}

void initializeMemoryManager() {
	for(int i = 0 ; i < MAXBLOCKS ; i++){
		blockStatus[i] = 0;
	}
}

void * requestMemorySpace(uint64_t requestedSpace) {

	int32_t n = getBlocksForSize(requestedSpace); //me must find n contiguous 0's in an array
	void * ret = (void *)(uintptr_t) -1;
	if (n == 0)
	{
		return ret;
	}
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
			ret = getBlockById(base);
			for (int i =  0; i < n; ++i)
			{
				blockStatus[base + i] = 1;
			}
			break;
		}
	}

	return ret;
}


void freeMemorySpace (void * freeBaseAddress,int32_t size){

	// printUint(size);
	// printUint((uint64_t)(uintptr_t) freeBaseAddress); // print addr 1
	int32_t sz = getBlocksForSize(size);
	int32_t id = getIdByAdress(freeBaseAddress); 

	for(int i = id ; i < sz + id  ; i++){
		blockStatus[i] = 0;
	}

}
