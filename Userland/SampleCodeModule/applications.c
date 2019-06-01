
#include "shell.h"
#include <stdint.h>
#include "applications.h"
#include "memory.h"
#include "modules.h"


static int i;


int initializeShortcutsArray(SHORTCUT scArr[]) {
	i = 0;
	loadShortcut(scArr, "numbers", (uintptr_t)&printNumbers);
	loadShortcut(scArr, "ps", (uintptr_t)&ps);
	loadShortcut(scArr, "clear", (uintptr_t)&clear);
	loadShortcut(scArr, "help", (uintptr_t)&help);
	loadShortcut(scArr, "time", (uintptr_t)&showTime);
	loadShortcut(scArr, "pong", (uintptr_t)&pong);
	loadShortcut(scArr, "exceptionInvalidOp", (uintptr_t)&exceptionInvalidOp);
	loadShortcut(scArr, "clear", (uintptr_t)&clear);
	loadShortcut(scArr, "prodCons", (uintptr_t)&prodCons);
	loadShortcut(scArr, "addProd", (uintptr_t)&addProd);
	loadShortcut(scArr, "addCons", (uintptr_t)&addCons);
	loadShortcut(scArr, "testMemoryManager", (uintptr_t)&testMemoryManager);
	loadShortcut(scArr, "lot", (uintptr_t)&testLottery);
	loadShortcut(scArr, "mut", (uintptr_t)&list_mutex);
	loadShortcut(scArr, "mut1", (uintptr_t)&mut1);
	loadShortcut(scArr, "mut2", (uintptr_t)&mut2);
	loadShortcut(scArr, "ipcs", (uintptr_t)&testIPC);
	loadShortcut(scArr, "trw", (uintptr_t)&testReadWriteIPC);
	loadShortcut(scArr, "trw1", (uintptr_t)&testReadWriteIPC2);
	loadShortcut(scArr, "trw2", (uintptr_t)&testReadWriteIPC3);
	loadShortcut(scArr, "pipe", (uintptr_t)&pipe);
	loadShortcut(scArr, "chpr", (uintptr_t)&changePriority);
	loadShortcut(scArr, "write2", (uintptr_t)&write2);
	loadShortcut(scArr, "read2", (uintptr_t)&read2);
	loadShortcut(scArr, "split", (uintptr_t)&split);
	loadShortcut(scArr, "unsplit", (uintptr_t)&unsplit);
	loadShortcut(scArr, "diph", (uintptr_t)&diph);
	return i;
}

void loadShortcut(SHORTCUT scArr[], char * id, uintptr_t ptr) {
	struct SHORTCUT shortcut;
	memcopy(shortcut.id, id, MAX_COMMAND_LENGTH);
	shortcut.pointer = (char *) ptr;
	scArr[i] = shortcut;
	i++;
}



