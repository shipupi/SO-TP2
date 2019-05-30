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
uint8_t os_addProcess(void * entryPoint , uint64_t priority,uint8_t foreground,uint64_t size, char * fdIn, char * fdOut);
void os_endProcess(int pid);
void os_listProcesses();
int os_pid();
void os_pstat();
void os_sleep();
int os_ipc_create (char * id, uint64_t size);
void os_ipc_write(char * id,char * string,uint64_t messageSize);
void os_ipc_read(char * id,char * string,uint64_t messageSize);
void os_sleepPID(int pid);
void os_wakePID(int pid);
void os_ipc_list();
void os_ipc_close(char *);
int os_mut_create(char * id);
int os_mut_request(char * id);
int os_mut_release(char * id);
int os_mut_delete(char * id);
void os_mut_list();
void os_pipe_create(char * pipeid);
void os_pipe_delete(char * pipeid);
void os_pipe_read(char * pipeid , char * buffer , int messageSize);
void os_pipe_write(char * pipeid , char * buffer , int messageSize);
void os_change_priority(uint64_t pid , int priority);
void os_split_screen();
void os_unsplit_screen();
void die();
#endif



