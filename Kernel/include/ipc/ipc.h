#ifndef IPC_H
#define IPC_H

#include <stdint.h>

#define ID_SIZE 40
#define MAX_QUEUE 100
#define MAX_IPCS 100
#define BLOCK_SIZE 255

typedef struct IPC{
    char id[ID_SIZE];
    int IPCcounter;
    void * address;
    uint64_t write;
    uint64_t read;
    uint64_t size;
    uint64_t unread;
    uint64_t free;
    uint64_t waiting;
    int64_t waitPids[MAX_QUEUE];
} IPC;

#endif

