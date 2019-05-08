#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "ipc/ipc.h"
#include "ipc/mutex.h"
#include "lib.h"

typedef char * ITEM;
typedef char * ID;
typedef char * MUTID;

#define ITEM_SIZE 20;

ITEM produceItem(MUTID id){
	ITEM item;
	item = requestMemorySpace(ITEM_SIZE);
	ipc_read(id,item,ITEM_SIZE);
	return item;
}

void consumeItem(MUTID id,ITEM item){
	ipc_write(MUTID id,item,ITEM_SIZE);
}

void producer(){
    while(true){
    	MUTID emptyCount = "mut1";
    	MUTID buffer_mutex = "mut2";
    	ITEM item;
    	item = requestMemorySpace(ITEM_SIZE);
        memcpy(item,produceITEM(buffer_mutex),ITEM_SIZE);
        
        mut_request(emptyCount);
        mut_request(buffer_mutex);
        ipc_write(buffer_mutex,item,ITEM_SIZE);
        mut_release(buffer_mutex);
        mut_release(emptyCount)
    }
}

void consumer(){
    while(true){
    	MUTID fillCount = "mut3";
    	MUTID buffer_mutex = "mut4";
        
        mut_request(fillCount);
        mut_request(buffer_mutex);
        ipc_read(buffer_mutex,item,ITEM_SIZE)
        mut_release(buffer_mutex);
        mut_release(fillCount);
        
        consumeItem(buffer_mutex,item);
    }
}

void prodcons(){
		//producer();
		//consumer();
}


//fillCount is the number of items already in the buffer and available to be read
//emptyCount is the number of available spaces in the buffer where items could be written




