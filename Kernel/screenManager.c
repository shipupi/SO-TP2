#include <stdint.h>
#include "drivers/vesaDriver.h"
#include "scheduler/PCB.h"
#include "ipc/ipc.h"
#include "screenManager.h"


char buf[MAXFDSIZE] = {'b',0};
void screenManager() {

	ipc_create(DEFAULT_FDOUT, MAXFDSIZE);
	while(1) {
		ipc_read(DEFAULT_FDOUT,buf, MAXFDSIZE);
		printWhiteString(buf);
	}

}