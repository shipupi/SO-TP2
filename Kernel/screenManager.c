#include <stdint.h>
#include "include/drivers/vesaDriver.h"
#include "include/scheduler/PCB.h"
#include "include/ipc/ipc.h"
#include "include/screenManager.h"

// LA 'b' esta puesta como placeholder para que reserve el lugar en el data segment y no en el bss
char buf[MAXFDSIZE] = {'b',0};


void screenManager() {

	ipc_create(DEFAULT_FDOUT, MAXFDSIZE);
	while(1) {
		ipc_read(DEFAULT_FDOUT,buf, MAXFDSIZE);
		printWhiteString(buf);
	}
}