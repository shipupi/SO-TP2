
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
	loadShortcut(scArr, "time", (uintptr_t)&time);
	loadShortcut(scArr, "pong", (uintptr_t)&pong);
	loadShortcut(scArr, "exceptionInvalidOp", (uintptr_t)&exceptionInvalidOp);
	loadShortcut(scArr, "clear", (uintptr_t)&clear);
	loadShortcut(scArr, "prodCons", (uintptr_t)&prodCons);
	loadShortcut(scArr, "testMemoryManager", (uintptr_t)&testMemoryManager);
	loadShortcut(scArr, "testScheduler", (uintptr_t)&testScheduler);
	loadShortcut(scArr, "test", (uintptr_t)&test);
	loadShortcut(scArr, "test2", (uintptr_t)&test2);
	loadShortcut(scArr, "mut", (uintptr_t)&mut);
	loadShortcut(scArr, "mut2", (uintptr_t)&mut2);
	loadShortcut(scArr, "mut1", (uintptr_t)&mut1);
	loadShortcut(scArr, "mut2", (uintptr_t)&mut2);
	loadShortcut(scArr, "ipcs", (uintptr_t)&ipcs);
	loadShortcut(scArr, "trw", (uintptr_t)&trw);
	loadShortcut(scArr, "trw1", (uintptr_t)&trw1);
	loadShortcut(scArr, "trw2", (uintptr_t)&trw2);

	return i;
}

void loadShortcut(SHORTCUT scArr[], char * id, uintptr_t ptr) {
	struct SHORTCUT shortcut;
	memcopy(shortcut.id, id, MAX_COMMAND_LENGTH);
	shortcut.pointer = (char *) ptr;
	scArr[i] = shortcut;
	i++;
}