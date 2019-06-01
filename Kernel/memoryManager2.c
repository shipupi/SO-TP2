#include <stdint.h>
#include "include/string.h"
#include "include/lib.h"
#include "include/kernel.h"
#include "include/memoryManager/memoryManager.h"
#include "include/drivers/vesaDriver.h"

static void * baseAddress = (void *)(uintptr_t) BASEADDRESS;

#define N 15 // 32768 = 2 ^ 15

// Data Structure, arbol al estilo heap
// Left child = 2*i + 1
// Right child = 2*i + 2

// Manteniendo la cantidad de bloques del otro memoryManager
/*
#define MAXBLOCKS 32768
#define BLOCKSIZE 4096
#define BASEADDRESS 0x900000
*/

// Cada bloque son 4096 mb
// Tengo 32768 bloques = 2 ^15
// 

// Necesito 2N - 1 nodos para representar todo el arbol, donde N = 2^15 = 32768

static char memoryNode[(2*MAXBLOCKS) - 1] = {1};


//Pongo todos los nodos vacios
void initializeMemoryManager(){
	for(int i = 0 ; i < MAXBLOCKS ; i++){
		memoryNode[i] = NODE_EMPTY;
	}
}
/*
 Cada nodo puede valer:
 	- 0 Totalmente vacio = NODE_EMPTY
 	- 1 Parcialmente vacio = NODE_PARTIAL
 	- 2 Ocupado = NODE_FULL
*/


int32_t getBlocksForSize(uint64_t requestedSize){
	if (requestedSize == 0) {
		return 0;
	}
	return ((requestedSize - 1)/ BLOCKSIZE)+1;
}

void * getAddressForIndex(int index) {
	int n = index + 1;

	/*printWhiteString("n //inex + 1: "); 
	printUint(n); 
	nextLine();*/

	int k = l2(n);

	/*printWhiteString("level(k): "); 
	printUint(k); 
	nextLine();*/

	int s = power(2,N-k);

	/*printWhiteString("step(s): "); 
	printUint(s); 
	nextLine();*/

	int p = n % power(2,k);

	/*printWhiteString("position(p): "); 
	printUint(p); 
	nextLine();*/

	int blockNumber = s * p ;

	printWhiteString("Requesting address for block: "); 
	printUint(index); 
	nextLine();
	printWhiteString("blockNumber: "); 
	printUint(blockNumber); 
	nextLine();

	return baseAddress + BLOCKSIZE * blockNumber;
}

int getIndexForAdress(int address , int size){

	address = address - (uint64_t) baseAddress;
	address = address / BLOCKSIZE;
	printWhiteString("address - baseAddress (/ size) : "); 
	printUint(address); 
	nextLine();

	int k = N - l2(size);
	printWhiteString("level(k): "); 
	printUint(k); 
	nextLine();

	int step = address/size;

	printWhiteString("step: "); 
	printUint(step); 
	nextLine();

	return power(2,k) - 1 + step ; // + offset - 1

}

void updateStatus(int index) {
	int leftVal = memoryNode[index * 2 + 1];
	int rightVal = memoryNode[index * 2 + 2];
	if(leftVal == NODE_FULL && rightVal == NODE_FULL) {
		memoryNode[index] = NODE_FULL;
	} else if(leftVal == NODE_EMPTY && rightVal == NODE_EMPTY) {
		// Aca no deberia caer nunca, pero por las dudas lo agrego
		memoryNode[index] = NODE_EMPTY;
	} else {
		memoryNode[index] = NODE_PARTIAL;
	}
}

void * requestNode(int index) {
	if(memoryNode[index] == NODE_EMPTY) {
		memoryNode[index] = NODE_FULL;
		return getAddressForIndex(index);
	} else {
		return 0;
	}
}

// Si esta funcion devuelve 0, es que no se encontro un bloque de memoria
// En este caso(como la funcion se llama recursivamente) no se actualiza el estado del padre
void * getBlock(int wantedBlockSize, int index, int currBlockSize) {
	if(currBlockSize == wantedBlockSize) {
		return requestNode(index);
	}
	
	if(memoryNode[index] == NODE_FULL) return 0;
	// Puede que tenga lugar, me fijo en ambas mitades
	// Empezando siempre por la izquierda
	void * left  = getBlock(wantedBlockSize, (index * 2 + 1), currBlockSize / 2);
	if(left != 0) {
		updateStatus(index);
		return left;
	}
	void * right  = getBlock(wantedBlockSize, (index * 2 + 2), currBlockSize /  2);
	if(right != 0) {
		updateStatus(index);
		return right;
	}
	return 0;
}

// If no block found returns 0
void * requestMemorySpace(uint64_t requestedSpace) {
	int64_t n = getBlocksForSize(requestedSpace);
	// Pasamos la cantidad de bloques pedidos a una potencia de 2
	n = upper_power_of_two(n);
	printWhiteString("Reqesting ");printUint(n); printWhiteString(" blocks"); nextLine();
	return getBlock(n, 0, 32768);
}

void freeMemorySpace (void * freeBaseAddress,int32_t size){

}




