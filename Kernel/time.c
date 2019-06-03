#include <drivers/time.h>
#include "include/scheduler/scheduler.h"
#include "include/drivers/vesaDriver.h"
#include "include/scheduler/sleeper.h"

static unsigned long ticks = 0;

static unsigned long lastSecs = 0;
#define TICKSPERQUANTUM 3

void timer_handler() {
	ticks++;
	unsigned long secs = seconds_elapsed();
	if(lastSecs != secs) {
		lastSecs = secs;
		wakeSleepers(secs);
	}
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
