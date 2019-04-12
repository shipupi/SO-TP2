#include "modules.h"
#include "syscalls.h"
#include "stdio.h"
#include "vidio.h"
#include "extra.h"


void help() {
	printf("\nHelp Manual for TPEG2");
	printf("\nclear:");
	printf("\n\tIt will clear the screen");
	printf("\ntime:");
	printf("\n\tIt will display on screen the current time in hh:mm:ss format");
	printf("\nexceptionDiv:");
	printf("\n\tIt will launch test program to verify the correct implementation of the handled exception: DivisionByZeroException");
	printf("\n\tException occurs when division by 0 is attempted");
	printf("\nexceptionInvalidOp:");
	printf("\n\tIt will launch test program to verify the correct implementation of the handled exception: WrongOpcodeException");
	printf("\n\tException occurs with the wrong use of operands");
	printf("\npong:");
	printf("\n\tIt will launch the game Pong");
	printf("\n\tUse WS and IK to move up and down the paddles. CTRL + c to exit the game.");
	printf("\nexit:");
	printf("\n\tcloses the terminal");
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
