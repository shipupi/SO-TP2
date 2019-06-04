#include "include/modules.h"
#include "include/syscalls.h"
#include "include/stdio.h"
#include "include/vidio.h"
#include "include/extra.h"
#include "include/testInvalidOp.h"

void help() {
	printf("\nHelp Manual for TPEG2");

	printf("\nclear:");
	printf("\n\tIt will clear the screen");

	printf("\ntime:");
	printf("\n\tIt will display on screen the current time in hh:mm:ss format");

	printf("\nbuddy:");
	printf("\n\tTests the memory manager");

	printf("\nnumbers:");
	printf("\n\tPrint numbers");

	printf("\nprodCons:");
	printf("\n\tsolution to the producers consumers problem");

	printf("\ntrw:");
	printf("\n\tCrea 4 IPC y los lista");

	printf("\ntrw1:");
	printf("\n\tEs un consumidor del IPC con id 'baj' (loop infinito) ");

	printf("\ntrw2:");
	printf("\n\tEs un productor del IPC con id 'baj' (solo una vez)");

	printf("\nmut:");
	printf("\n\tlist mutexes");

	printf("\nmut1:");
	printf("\n\tEs un consumidor del MUTEX con id 'test (loop infinito)'");

	printf("\nmut2:");
	printf("\n\tEs un productor del MUTEX con id 'test (solo una vez)'");

	printf("\nps:");
	printf("\n\tlist proccesses");

	printf("\nlot:");
	printf("\n\ttest the lottery scheduling with two processes of differnt priorities");

	printf("\nipcs:");
	printf("\n\tipcs");

	printf("\nchpr:");
	printf("\n\tChange the priority of a process chpr pid newPriority");

	printf("\nfilo:");
	printf("\n\tFisolofos");

	printf("\nsplit:");
	printf("\n\t Split the terminal in background and foreground");

	printf("\nwrite2:");
	printf("\n\t Writes the number 2 indefinitely");

	printf("\nread2:");
	printf("\n\t Reads and multiply by 2 the input");


	
}

void showTime() {
	printf("\nCurrent time = ");
	uint64_t * currTime = os_time();		//returns an array with the current hour, minutes, and seconds

	char time[9];					//pass the array to a string to print
	time[0] = currTime[0] + '0';
	time[1] = currTime[1] + '0';
	time[2] = ':';
	time[3] = currTime[2] + '0';
	time[4] = currTime[3] + '0';
	time[5] = ':';
	time[6] = currTime[4] + '0';
	time[7] = currTime[5] + '0';
	time[8] = 0;

	printf(time);
}


int div(int n) {
	return 10/n;
}

//Creado para conocer la cantidad de ticks por segundo para que aunque el timer tick sea 
//distinto, el pong funcione con la misma velocidad. No logramos hacer que funcione bien por varias 
//razones entonces vamos a tomar 18 ticks por segundo por como esta definido en el kernel space 

int ticksPerSecond() {
	return 18;
/*
	int secondsTotal;
	int ticksTotal;
	double i = 0;
	int ticksStart = os_ticks();
	int secondStart = os_sec();

	do {
		while(i < 100000){		//HORRIBLE VER SI SE PUEDE HACER DE OTRA MANERA
			i += 0.1;
		}
	while((secondsTotal = os_sec() - secondStart) == 0);
	ticksTotal = os_ticks() - ticksStart;
	return ticksTotal/secondsTotal;
	*/
}

void exceptionDiv0() {
	printf("\nDividing by zero");
	div(0);
}

void exceptionInvalidOp() {
	printf("\nAttempting a jmp 0x0");
	invalidOpTest();
}

void clear() {
	os_clear();
}
