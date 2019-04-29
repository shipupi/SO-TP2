#include <time.h>
#include <scheduler.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;

	// Aca se ejecuta el context switch?
	schedule();

}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
