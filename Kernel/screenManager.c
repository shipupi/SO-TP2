#include <stdint.h>
#include "include/drivers/vesaDriver.h"
#include "include/scheduler/PCB.h"
#include "include/ipc/ipc.h"
#include "include/screenManager.h"
#include "include/scheduler/scheduler.h"

// LA 'b' esta puesta como placeholder para que reserve el lugar en el data segment y no en el bss
char buf[MAXFDSIZE] = {'b',0};
char buf2[MAXFDSIZE] = {'b',0};


void screenManager() {
	ipc_create(DEFAULT_FDIN,MAXFDSIZE);
	ipc_create(DEFAULT_FDOUT, MAXFDSIZE);
	ipc_create(INVALID_FD, MAXFDSIZE);
	while(1) {
		ipc_read(DEFAULT_FDOUT,buf, MAXFDSIZE);
		printWhiteString(buf);
	}
}


// In development. SCreen manager 2 supporting a split screen!
void screenManager2() {
	while(1) {
		ipc_read(SPLIT_FD, buf2, MAXFDSIZE);
		printString(buf2, 255, 255, 255, 2);
	}

}

void splitScreen() {
	// printWhiteString("(screen manager) splitting screen....");
	ipc_create(SPLIT_FD, MAXFDSIZE);
	vesa_addSplit();
	addProcess(&screenManager2, 1,2,50, SPLIT_FD, INVALID_FD);
}

void unsplitScreen() {
	vesa_removeSplit();
	printWhiteString("(screen manager) usplitting screen....");
}