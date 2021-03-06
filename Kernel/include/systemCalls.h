
#ifndef SYSTEMCALLS_H
#define SYSTEMCALLS_H

#include <stdint.h>

#define STDIN 0
#define STDOUT 1

void * getSyscallFunction(int number);
int sys_ticks(int * result);
int sys_sec(int * result);
uint64_t sys_read(uint64_t fd, char *buffer, uint64_t size);
uint64_t sys_write(uint64_t fd, char *buffer, uint64_t size);
uint64_t * sys_time(uint64_t * timeArray);
void sys_pixel(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b);
void sys_clear();
void sys_beep();
void sys_unbeep();
void * sys_requestMemorySpace(uint64_t requestedSpace);
void sys_freeMemorySpace (void * freeBaseAddress,int32_t size);
void sys_schedule();
uint8_t sys_addProcess(void * entryPoint,uint64_t priority,uint8_t foreground,uint64_t size,char * fdIn,char * fdOut);
void sys_endProcess(int pid);
void sys_listProcesses();
int sys_pid();
void sys_pstat(void * pcbAddr);
void sys_sleep_seconds(int seconds);
void sys_ipc_create(char * id,uint64_t size);
void sys_ipc_write(char * id,char * string,uint64_t messageSize);
void sys_ipc_read(char * id,char * string,uint64_t messageSize);
void sys_sleepPID(int pid);
void sys_wakePID(int pid);
void sys_ipc_list();
void sys_ipc_close(char *);
int sys_mut_create(char * id);
int sys_mut_request(char * id);
int sys_mut_release(char * id);
int sys_mut_delete(char * id);
void sys_mut_list();
void sys_halt();
void timer_tick();
void sys_pipe_create(char * pipeid);
void sys_pipe_delete(char * pipeid);
void sys_pipe_read(char * pipeid , char * buffer , int messageSize);
void sys_pipe_write(char * pipeid , char * buffer , int messageSize);
void sys_change_priority(uint64_t pid , int priority);
void sys_split_screen();
void sys_unsplit_screen();
#endif /* SYSTEMCALLS_H */