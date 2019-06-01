#ifndef SLEEPER_H
#define SLEEPER_H

#include <stdint.h>


void sleep_seconds(int seconds);
void wakeSleepers(int currentSeconds);
// SB SLeep block
typedef struct Sleeper {
	uint64_t pid;
	uint64_t sec_end;
	struct Sleeper* next;
} Sleeper;

#endif