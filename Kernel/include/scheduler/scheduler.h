#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>


#define MAXPROCESSES 256
#define PROCESSSTACKSIZE 4096

int rand();
void * schedule(void * oldStack);
uint8_t addProcess(void * entryPoint,uint64_t priority,uint8_t foreground,uint64_t size,char * fdIn,char * fdOut);
void endProcess(int pid);
void listProcesses();
void runProcess(uintptr_t entryPoint);
void sleepPID(int pid);
void wakePID(int pid);
void sleep();
void changePriority(uint64_t pid , int priority);
int pid();
void process_status(void * pcbAddr);

char * getFdIn();
char * getFdOut();
#endif


