#include "shell.h"
#include "modules.h"
#include "string.h"
#include "include/stdio.h"
#include "syscalls.h"
#include "applications.h"

#define BLOCKSIZE 4096
#define BASEADDRESS 0x900000
#define BLOCKSIZE 4096

static void * baseAddress = (void *)(uintptr_t) BASEADDRESS;

int getnum(char * msg){
  printf("\n");
  char * command = os_requestMemorySpace(200);
  printf("introduce a number ");
  printf(msg);
  printf(": ");
  scanf(command, MAX_COMMAND_LENGTH);
  return to_num(command,strlen(command));
}

int testMemoryManager(){

  printf("Buddy\n");
  printf("Type in any of the following commands: \n");
  printf("request\n");
  printf("free\n");
  printf("end\n");

  char * command = os_requestMemorySpace(200);
  int exit = 0;
  while(!exit){
      printf("\nshell/testMemoryManager$>");
      scanf(command, MAX_COMMAND_LENGTH);
      //printf(command);
      if(strcmp(command,"request")==0){
        int blocks = getnum("blocks");
        printf("\nRequest ");
        puint(blocks);
        printf(" blocks\n");
        
        void * addr;
        addr = os_requestMemorySpace(blocks*BLOCKSIZE);
        if(addr){
          addr = addr - (uint64_t) baseAddress;
          addr = (void*)((uintptr_t)addr / BLOCKSIZE);
          printf("address: ");
          puint((uintptr_t)addr);
          printf("\n");
        } else {
          printf("No blocks found\n");
        }

      }
      else if(strcmp(command,"free")==0){
        void * address = (void*)(uintptr_t)getnum("address");
        
        int blocks = getnum("blocks");
        printf("\nFree address ");
        puint((uintptr_t)address);
        printf(" of size ");
        puint(blocks);
        printf("\n");
        
        address = (void*)((uint64_t) address * BLOCKSIZE);
        address = address + (uint64_t)baseAddress;
        
        os_freeMemorySpace(address,(uint32_t)blocks);
      
      }
      else if(strcmp(command,"end")==0){
          exit = 1;
      }
      else{
        printf("\n?\n");
      }
      command = "";
  }
   
	return 0;
  }






