#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "PCB.h"


#define ITEM_SIZE 5
#define ITEM_VAL "hola"
#define FILL_MUTEX "fillMut"
#define BUFFER_MUTEX "buffMut"
#define EMPTY_MUTEX "emptyMut"
#define IPC_SIZE 10
#define IPC_NAME "prodcon"


// Codigo sacado de wikipedia: https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
// procedure producer() 
// {
//     while (true) 
//     {
//         item = produceItem();
//         down(emptyCount);
//         down(buffer_mutex);
//         putItemIntoBuffer(item);
//         up(buffer_mutex);
//         up(fillCount);
//     }
// }

// procedure consumer() 
// {
//     while (true) 
//     {
//         down(fillCount);
//         down(buffer_mutex);
//         item = removeItemFromBuffer();
//         up(buffer_mutex);
//         up(emptyCount);
//         consumeItem(item);
//     }
// }

// Codigo adaptado:
void producer(){
    while(1){
        os_mut_request(EMPTY_MUTEX);
        os_mut_request(BUFFER_MUTEX);
        os_ipc_write(IPC_NAME, ITEM_VAL, ITEM_SIZE);
        os_mut_release(BUFFER_MUTEX);
        os_mut_release(FILL_MUTEX);
    }
}

void consumer(){
    while(1){
        char item[ITEM_SIZE];
        os_mut_request(FILL_MUTEX);
        os_mut_request(BUFFER_MUTEX);
        os_ipc_read(IPC_NAME,item,ITEM_SIZE);
        os_mut_release(BUFFER_MUTEX);
        os_mut_release(EMPTY_MUTEX);
        printf(item);
        printf("\n");
    }
}

void prodCons(){
    os_mut_create(EMPTY_MUTEX);
    os_mut_create(FILL_MUTEX);
    os_mut_create(BUFFER_MUTEX);
    os_ipc_create(IPC_NAME, IPC_SIZE);
    os_addProcess(&producer,10,'c',PCB_BACKGROUND,4000);
    os_addProcess(&consumer,1,'c',PCB_BACKGROUND,4000);
}


//fillCount is the number of items already in the buffer and available to be read
//emptyCount is the number of available spaces in the buffer where items could be written




