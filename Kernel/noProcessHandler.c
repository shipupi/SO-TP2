
#include "include/ipc/ipc.h"
#include "include/utils.h"
void noProcessHandler() {
	while(1) {
		halt();
	}
}