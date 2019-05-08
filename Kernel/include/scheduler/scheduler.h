#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>

void schedule();
uint8_t addProcess(void * entryPoint,uint64_t priority,char name,uint8_t foreground,uint64_t size);
void endProcess(int pid);
void listProcesses();
void runProcess(uintptr_t entryPoint);
void sleepPID(int pid);
void wakePID(int pid);
void sleep();

int pid();
#endif