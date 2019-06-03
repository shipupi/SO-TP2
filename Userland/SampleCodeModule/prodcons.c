#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "PCB.h"


#define ITEM_VAL "hola"
#define FILL_MUTEX "fillMut"
#define BUFFER_MUTEX "buffMut"
#define EMPTY_MUTEX "emptyMut"
#define ITEM_SIZE 5
#define IPC_SIZE 10
#define IPC_NAME "prodcon"
#define PROCESS_MEMORY 4000
#define SECOND_INTERVAL 10


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
    os_ipc_create(IPC_NAME, IPC_SIZE);
    while(1){
        os_ipc_write(IPC_NAME, ITEM_VAL, ITEM_SIZE);
    }
}

void consumer(){
    os_ipc_create(IPC_NAME, IPC_SIZE);
    while(1){
        char item[ITEM_SIZE];
        os_ipc_read(IPC_NAME,item,ITEM_SIZE);
        // printf(item); Producer output commented not to flood the shell
        // printf("\n");
    }
}

void addProd() {
    os_addProcess(&producer, 1, PCB_BACKGROUND, PROCESS_MEMORY,"","");
    printf("Added producer Successfully\n");
}

void addCons() {
    os_addProcess(&consumer, 1, PCB_BACKGROUND, PROCESS_MEMORY,"","");
    printf("Added consumer Successfully\n");
}

void prodCons(){
    PCB p;
    os_pstat(&p);
    if (p.foreground == PCB_FOREGROUND)
    {
        printf("This application can only be run on the background\n");
        return;
    }
    os_mut_create(EMPTY_MUTEX);
    os_mut_create(FILL_MUTEX);
    os_mut_create(BUFFER_MUTEX);
    os_ipc_create(IPC_NAME, IPC_SIZE);
    printf("This is only the watcher process, it will print the IPC list every 10 seconds\n");
    printf("You can add Producers or consumers by using addProd or addCons\n");
    printf("As of now this application cannot be killed, so if you are tired of it, restart the computer :(\n");
    printf("Also, it will run on busyWaiting, until a timed sleep syscall is implemented :(\n");
    printf("Finally, if the PC has been on for too long for the second counter to reset, there may be some bug (untested) \n");
    uint64_t lastSec = os_sec();
    uint64_t currSec;
    while(1) {
        currSec = os_sec();
        if ( currSec - lastSec >= SECOND_INTERVAL) {
            os_ipc_list();
            lastSec = currSec;
        }
    }
}


//fillCount is the number of items already in the buffer and available to be read
//emptyCount is the number of available spaces in the buffer where items could be written




