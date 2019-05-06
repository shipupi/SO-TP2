
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
	return i;
}

void loadShortcut(SHORTCUT scArr[], char * id, uintptr_t ptr) {
	struct SHORTCUT shortcut;
	memcopy(shortcut.id, id, MAX_COMMAND_LENGTH);
	shortcut.pointer = (char *) ptr;
	scArr[i] = shortcut;
	i++;
}