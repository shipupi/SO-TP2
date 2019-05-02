#include <time.h>
#include <scheduler.h>
#include "include/vesaDriver.h"

static unsigned long ticks = 0;

#define TICKSPERQUANTUM 3

void timer_handler() {
	ticks++;
	// printWhiteString("a");
	// Scheduling
	int systemready = 1;
	if (systemready) {
		// Context switch
		
		// Schedule
		if (ticks % TICKSPERQUANTUM == 0) {
			schedule();
		}
	}
	// End Scheduling
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
