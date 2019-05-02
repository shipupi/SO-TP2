#include <naiveLegacy/naiveClock.h>
#include <naiveLegacy/naiveConsole.h>


#define SECONDS 00
#define MINUTES 02
#define HOURS 04


uint64_t getSeconds(){
	return getTime(SECONDS);
}
uint64_t getMinutes(){
	return getTime(MINUTES);
}
uint64_t getHours(){
	return getTime(HOURS);
}



