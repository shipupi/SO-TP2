#include <stdint.h>
#include <string.h>
#include "include/lib.h"
#include "include/moduleLoader.h"
#include "include/memoryManager/memoryManager.h"
#include "include/naiveLegacy/naiveConsole.h"
#include "include/naiveLegacy/naiveClock.h"
#include "include/drivers/naiveKeyboard.h"
#include "include/idtLoader.h"
#include "include/interrupts.h"
#include "include/drivers/time.h"
#include "include/drivers/vesaDriver.h"
#include "include/scheduler/scheduler.h"
#include "include/scheduler/PCB.h"

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
	/*void * addr1;
	void * addr2;

	addr1 = requestMemorySpace(32768*BLOCKSIZE);
	if(addr1) {
		printUint((uintptr_t)addr1);
	} else {
		pl("No blocks found");
	}
	nextLine();

	addr2 = requestMemorySpace(16);
	if(addr2) {
		printUint((uintptr_t)addr2);
	} else {
		pl("No blocks found");
	}
	nextLine();

*/

	/*
	initializeMemoryManager();
	void * addr1;
	addr1 = requestMemorySpace(32768);
	//addr1 = requestMemorySpace(134217728 / 2 - 1); 
	// addr1 = requestMemorySpace(4096 * 2 + 1);
	if(addr1) {
		printUint((uintptr_t)addr1);
	} else {
		pl("No blocks found");
	}
	*/
/*
	pl("-----------");

	nextLine();
	pl("BASEADDRESS: ");
	printUint((uintptr_t) BASEADDRESS );
	nextLine();

	printUint((uintptr_t)getAddressForIndex(0));

	nextLine();

	printUint((uintptr_t)getAddressForIndex(1));

	nextLine();

	printUint((uintptr_t)getAddressForIndex(2));

	nextLine();

	printUint((uintptr_t)getAddressForIndex(3));

	nextLine();

	printUint((uintptr_t)getAddressForIndex(4));

	nextLine();

	printUint((uintptr_t)getAddressForIndex(5));

	nextLine();

	printUint((uintptr_t)getAddressForIndex(6));

	nextLine();

	printUint((uintptr_t)getAddressForIndex(7));

	nextLine();

	//nextLine();

	//printUint((uintptr_t)getAddressForIndex(8));

	//nextLine();

	pl("-----------");
*/
/*
	pl("-----------");

	nextLine();
	
	printUint(getIndexForAdress(9437184,32768));
	
	nextLine();

	printUint(getIndexForAdress(9437184,16384));
	
	nextLine();

	printUint(getIndexForAdress(76546048,16384));
	
	nextLine();

	printUint(getIndexForAdress(9437184,8192));
	
	nextLine();

	nextLine();

	printUint(getIndexForAdress(42991616,8192));
	
	nextLine();

	nextLine();

	printUint(getIndexForAdress(76546048,8192));
	
	nextLine();

	printUint(getIndexForAdress(110100480,8192));
	
	nextLine();

	printUint(getIndexForAdress(9437184,4096));
	
	nextLine();

	pl("-----------");
*/
	addProcess(sampleCodeModuleAddress, 1, 'a', 2, 50);
	load_idt();
	/*while(1) {
		_hlt();
	}
	return 0;*/
}



