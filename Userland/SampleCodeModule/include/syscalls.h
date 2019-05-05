#include <stdint.h>
#ifndef SYSCALLS_H
#define SYSCALLS_H

int os_ticks(void);
int os_sec(void);
uint64_t read(uint64_t fd, char *buffer, uint64_t size);
uint64_t write(uint64_t fd, char *buffer, uint64_t size);
uint64_t * os_time(void);
uint64_t os_draw(uint64_t x, uint64_t y, uint64_t red,uint64_t green,uint64_t blue);
void os_clear(void);
void os_beep();
void os_unbeep();
void * os_requestMemorySpace(uint64_t requestedSpace);
void os_freeMemorySpace (void * freeBaseAddress,int32_t size);
void os_schedule();
uint8_t os_addProcess(void * entryPoint , uint64_t priority , char name,uint8_t foreground,uint64_t size);
void os_endProcess(int pid);
void os_listProcesses();
void os_sleep();
int os_ipc_create (char * id, uint64_t size);
void os_ipc_write(char * id,char * string,uint64_t messageSize);
void os_ipc_read(char * id,char * string,uint64_t messageSize);
void os_sleepPID(int pid);
void os_wakePID(int pid);
void os_ipc_list();
void os_ipc_close(char *);
#endif

