#include <time.h>
#include <scheduler.h>
#include "include/vesaDriver.h"

static unsigned long ticks = 0;

#define TICKSPERQUANTUM 3

void timer_handler() {
	ticks++;

	if (ticks % TICKSPERQUANTUM == 0)
	{
		schedule();
	}
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
