#include "include/applications.h"
#include "include/syscalls.h"
#include "include/stdio.h"

static int splitVal = 0;

void split() {
	splitVal = 1;
	os_split_screen();
}

void unsplit() {
	splitVal = 0;
	os_unsplit_screen();
}

int isSplit() {
	return splitVal;
}