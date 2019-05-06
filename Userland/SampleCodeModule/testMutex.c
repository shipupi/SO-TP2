#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
void test_mutex(){
	printf("\nMUTEX\n");
	os_mut_create("abc");
	os_mut_create("ab");
	os_mut_create("c");
	os_mut_create("d");
	os_mut_create("e");
	os_mut_create("f");
	os_mut_request("a");
	os_mut_release("a");
	os_mut_delete("a");
	os_mut_list();
	
}
