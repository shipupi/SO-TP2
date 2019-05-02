#include <stdint.h>
#include <string.h>
#include "include/lib.h"
#include "include/moduleLoader.h"
#include "include/memoryManager.h"
#include "include/naiveConsole.h"
#include "include/naiveClock.h"
#include "include/naiveKeyboard.h"
#include "include/idtLoader.h"
#include "include/time.h"
#include "include/vesaDriver.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

int main();

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase() {
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);

	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

void reboot() 
{
	main();
}

int main()
{	
	initializeMemoryManager();
	load_idt();
	
	
	// TEST DE MEMORY MANAGER
	// void * addr1 = requestMemorySpace(5000); // Request de 2 bloques (Deberia dar base Address = 0x900000
 //    printUint((uint64_t)(uintptr_t) addr1); // print addr 1
 //    nextLine();
 //    printUint((uint64_t)(uintptr_t) requestMemorySpace(50)); // request de 1 bloque (Deberia imprimir 0x900000 + 4096 * 2)
 //    nextLine();
    // freeMemorySpace (addr1,5000); // Libero los primeros 2 bloques
    // printUint((uint64_t)(uintptr_t) requestMemorySpace(10000)); // request de 3 bloque (Deberia imprimir 0x900000 + 4096 * 3)
    // nextLine();
    // printUint((uint64_t)(uintptr_t) requestMemorySpace(6000)); // request de 2 bloque (Deberia imprimir 0x900000)

	


    ((EntryPoint)sampleCodeModuleAddress)();
	return 0;
}
