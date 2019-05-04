#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>

void schedule();
uint8_t addProcess(void * entryPoint,uint64_t priority,char name,uint8_t foreground,uint64_t size);
void endProcess(int pid);
void listProcesses();
#endif