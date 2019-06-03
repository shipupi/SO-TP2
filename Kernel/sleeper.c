
#include <stdint.h>
#include "include/scheduler/scheduler.h"
#include "include/scheduler/sleeper.h"
#include "include/drivers/time.h"
#include "include/memoryManager/memoryManager.h"
#include "include/ipc/ipc.h"
#include "include/drivers/vesaDriver.h"

static Sleeper* head = 0;

// typedef struct Sleeper {
// 	uint64_t pid;
// 	uint64_t sec_end;
// 	struct Sleeper* next;
// } Sleeper;


// Linked list trucha
void sleep_seconds(int seconds) {
	int p;
    p = pid();
    int end = seconds_elapsed() + seconds;
    Sleeper* newSleeper = (Sleeper*) requestMemorySpace((uint64_t) sizeof(Sleeper));
    newSleeper->pid = p;
    newSleeper->sec_end = end;
    newSleeper->next = 0;

    Sleeper* s = head;

    if(s == 0) {
    	head  = newSleeper;
 	    ipc_sleep(); // Lo pongo a dormir hasta que lo despierte wakesleepers
    	return;
    } else if(s->sec_end > newSleeper->sec_end) {
    	newSleeper->next = head;
    	head = newSleeper;
        ipc_sleep();
        return;
    }

    while(s->next != 0) {
    	if(s->next->sec_end > newSleeper->sec_end) {
    		newSleeper->next = s->next;
    		s->next = newSleeper;
    		ipc_sleep(); // Lo pongo a dormir hasta que lo despierte wakesleepers
    		return;
    	}
    	s = s->next;
    }
    s->next = newSleeper;

    ipc_sleep(); // Lo pongo a dormir hasta que lo despierte wakesleepers
    return;
}

void wakeSleepers(int currentSeconds) {
	while(head != 0 && head->sec_end <= currentSeconds) {
		wakePID(head->pid);
		head = head->next;
	}
}