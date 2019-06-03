#ifndef MUT_H
#define MUT_H
int mut_create(char * id);
int mut_request(char * id);
int mut_release(char * id);
int mut_delete(char * id);
void mut_list();

#include "./ipc.h"

#define MAX_MUTS 2000

typedef struct MUT{
	char id[ID_SIZE];
	int value;
	uint64_t waiting;
    int64_t waitPids[MAX_QUEUE];
}MUT;

#define MUT_UNLOCKED 2
#define MUT_LOCKED 1
#endif