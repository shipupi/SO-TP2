#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
int testMemoryManager(){
	//TEST DE MEMORY MANAGER

  printf("\nDEMO\n");

	printf("\nRequest de 2 bloques (Deberia dar base Address = Stack Address proceso con mayor stack Address\n");
	void * addr1 = os_requestMemorySpace(5000); 
	printUint((uint64_t)(uintptr_t) addr1);

 	printf("\nRequest de 1 bloque (Deberia imprimir base Address + 4096 * 2)\n");
 	void * addr2 = os_requestMemorySpace(50)
  printUint((uint64_t)(uintptr_t) addr2); 
 	
  printf("\nLibero los primeros 2 bloques\n"); 
  os_freeMemorySpace(addr1,5000); 
   
  printf("\nRequest de 3 bloque (Deberia imprimir base Address + 4096 * 3)\n");
  void * addr3 = os_requestMemorySpace(6000);
  printUint((uint64_t)(uintptr_t) os_requestMemorySpace(10000)); 
    
  printf("\nRequest de 2 bloque (Deberia imprimir base Address)\n");
  printUint((uint64_t)(uintptr_t) addr3);

  os_freeMemorySpace(addr1,5000);
  os_freeMemorySpace(addr2,50);
  os_freeMemorySpace(addr3,6000);
/*
  printf("\nINTERACTIVE\n");

  int exit = 0;

  while(!exit){
      printf("\nshell/testMemoryManager$>");
      scanf(command, MAX_COMMAND_LENGTH);
  }
*/   
	return 0;
  }

