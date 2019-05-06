#include <drivers/time.h>
#include "include/scheduler/scheduler.h"
#include "include/drivers/vesaDriver.h"

static unsigned long ticks = 0;

#define TICKSPERQUANTUM 3

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
