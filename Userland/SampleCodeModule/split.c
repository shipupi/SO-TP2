#include "include/applications.h"
#include "include/syscalls.h"
#include "include/stdio.h"
#include "include/PCB.h"

static int splitVal = 0;

void split() {

	PCB* p = os_requestMemorySpace(sizeof(PCB));
	os_pstat(p);
	if (p->foreground == PCB_FOREGROUND)
	{
		printf("This application can only be run on the background\n");
		return;
	}
	os_freeMemorySpace(p, sizeof(PCB));

	splitVal = 1;
	os_split_screen();
	printf("Creado split . que pasa?\n");
}

void unsplit() {
	splitVal = 0;
	os_unsplit_screen();
}

int isSplit() {
	return splitVal;
}