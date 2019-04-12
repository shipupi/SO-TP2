#include <stdint.h>
#include <systemCalls.h>
#include "naiveKeyboard.h"
#include "naiveClock.h"
#include "vesaDriver.h"
#include "soundDriver.h"
#include "time.h"

int sys_ticks(int * result) {
	*result = ticks_elapsed();
	return *result;
}

int sys_sec (int * result) {
	*result = seconds_elapsed();
	return *result;
}

//We will only read from the keyboard buffer for this project --> fd = 0 (stdin)
uint64_t sys_read(uint64_t fd, char *buffer, uint64_t size){
	uint64_t bytesRead = 0;
	char c;
	if (fd == STDIN){							//read from the keyboard buffer (stdin)
		while(size > 0 && (c = getChar())) {	//getChar returns 0 when the keboard buffer is empty
			buffer[bytesRead++] = c;
			size--;
		}
	}
	return bytesRead;
}

//We will only write to the screen for this project --> fd = 1 (stdout)
uint64_t sys_write(uint64_t fd, char *buffer, uint64_t size){
	uint64_t bytesRead = 0;

	if (fd == STDOUT) {
		while(size--) {
			char c = *buffer;
			if (c == '\n') {
				nextLine();
			} else if (c == '\b') {
				deleteChar();
			} else {
				printChar(c,255,255,255);
			}
			buffer++;
			bytesRead++;
		}
	}

	return bytesRead;
}

uint64_t * sys_time(uint64_t * timeArray) {
	//2 for hour, 2 for minutes, 2 for seconds
	uint64_t hour = getHours();
	uint64_t min = getMinutes();
	uint64_t sec = getSeconds(); 

	switch(hour){
		case 0: hour = 21;
				break;
		case 1: hour = 22;
				break;
		case 2: hour = 23;
				break;
		default: hour -= 3;
	}

	timeArray[0] = hour/10;
	timeArray[1] = hour%10;
	timeArray[2] = min/10;
	timeArray[3] = min%10;
	timeArray[4] = sec/10;
	timeArray[5] = sec%10;;
	return timeArray;
}

void sys_pixel(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b) {
	putPixel(x,y,r,g,b);
}

//It clear the screen and goes back to original starting point
void sys_clear() {
	clearAll();
}

//Play sound
void sys_beep() {
	playSound();
}

//Stop sound
void sys_unbeep() {
	stopSound();
}