#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>

void schedule();
uint8_t addProcess(void * entryPoint);
void endProcess(int pid);
void listProcesses();
#endif