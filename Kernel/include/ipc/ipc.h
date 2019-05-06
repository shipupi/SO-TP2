#ifndef IPC_H
#define IPC_H

#include <stdint.h>

#define ID_SIZE 40

typedef struct IPC{
    char id[ID_SIZE];
    int IPCcounter;
    void * address;
    uint64_t write;
    uint64_t read;
    uint64_t size;
    uint64_t unread;
    uint64_t free;
} IPC;

#endif





