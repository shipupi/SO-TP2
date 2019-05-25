#include <stdint.h>
#include <systemCalls.h>
#include "drivers/naiveKeyboard.h"
#include "naiveLegacy/naiveClock.h"
#include "drivers/vesaDriver.h"
#include "drivers/soundDriver.h"
#include "drivers/time.h"
#include "memoryManager/memoryManager.h"
#include "scheduler/scheduler.h"
#include "include/ipc/ipc.h"
#include "include/ipc/mutex.h"


#define SYSCALLNUMBER 11

static void * systemCallsArray[] = {
		&sys_ticks,
		&sys_sec,
		&sys_read,
		&sys_write,
		&sys_time,
		&sys_pixel,
		&sys_clear,
		&sys_beep,
		&sys_unbeep,
		&sys_requestMemorySpace,
		&sys_freeMemorySpace
};

void * getSyscallFunction(int number) {
	return systemCallsArray[number];	
}

int sys_ticks(int * result) {
	*result = ticks_elapsed();
	return *result;
}

int sys_sec (int * result) {
	*result = getSeconds();
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

// MEMORY SYSCALLS
void * sys_requestMemorySpace(uint64_t requestedSpace) {
	return requestMemorySpace(requestedSpace);
}

void sys_freeMemorySpace (void * freeBaseAddress,int32_t size) {
	freeMemorySpace(freeBaseAddress,size);
}

// Processes
void sys_schedule() {
	schedule();
}
uint8_t sys_addProcess(void * entryPoint,uint64_t priority,char name,uint8_t foreground,uint64_t size) {
	return addProcess(entryPoint,priority,name,foreground,size);
}
void sys_endProcess(int pid) {
	endProcess(pid);
}
void sys_listProcesses() {
	listProcesses();
}

void sys_sleep(){
	printWhiteString("SLEEP");
}

void sys_ipc_create(char * id,uint64_t size){
	ipc_create(id,size);
}

void sys_ipc_write(char * id, char * string, uint64_t messageSize){
	ipc_write(id, string, messageSize);
}

void sys_ipc_read(char * id, char * string, uint64_t messageSize){
	ipc_read(id,string,messageSize);
}

void sys_sleepPID(int pid){
	printWhiteString("SLEEP_PID ");
	printInt(pid);
	sleepPID(pid);
}

void sys_wakePID(int pid){
	printWhiteString("WAKE_PID");
	printInt(pid);
	wakePID(pid);
}

void sys_ipc_list(){
	ipc_list();
}

void sys_ipc_close(char * id){

}

int sys_mut_create(char * id){
	mut_create(id);
	return 0;
}
int sys_mut_request(char * id){
	mut_request(id);
	return 0;
}
int sys_mut_release(char * id){
	mut_release(id);
	return 0;
}
int sys_mut_delete(char * id){
	mut_delete(id);
	return 0;
}
void sys_mut_list(){
	mut_list();
}

int  sys_pid() {
	return pid();
}

void sys_pstat(void * pcbAddr) {
	process_status(pcbAddr);
	return;
}

void sys_pipe_create(char * pipeid){
	pipe_create(pipeid);
	return;
}

void sys_pipe_delete(char * pipeid){
	pipe_delete(pipeid);
	return;
}

void sys_pipe_read(char * pipeid , char * buffer , int messageSize){
	pipe_read(pipeid,buffer,messageSize);
	return;
}

void sys_pipe_write(char * pipeid , char * buffer , int messageSize){
	pipe_write(pipeid,buffer,messageSize);
	return;
}
