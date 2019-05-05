#include "syscalls.h"
void sleep(){
	os_sleep();
}

void sleepPID(int pid){
	os_sleepPID(pid);
}

void wakePID(int pid){
	os_wakePID(pid);
}