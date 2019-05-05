#ifndef IPC_H
#define IPC_H

#include <stdint.h>

#define ID_SIZE 40

typedef struct IPC{
    char id[ID_SIZE];
    void * address;
    int i;
} IPC;

#endif





