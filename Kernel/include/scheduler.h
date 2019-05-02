#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>

void schedule();
uint8_t addProcess(void * entryPoint);
void endProcess(void * stackAddress);
void listProcesses();
#endif