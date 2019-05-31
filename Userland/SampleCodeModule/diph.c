#include "shell.h"
#include "modules.h"
#include "string.h"
#include "stdio.h"
#include "syscalls.h"
#include "applications.h"
#include "include/PCB.h"
#define N 4

uint8_t philosophers[N];
int philos;

int id = 5;

int random(){
	return 5;
}

void think(int time){
	while(10000*time){

	}
}

void eat(){
	int r = random();
	while(10000*r){

	}
}

void philosopher(){
	int i = 0;
	//THINKING
	while(1){
		think(random());
		char * s;
		if(id%2==0){

			//HUNGRY

    		numberToString(id,s);
			os_mut_request(s);
			numberToString(id+1,s);
			os_mut_request(s);
			
			//EATING

			eat();

			numberToString(id,s);
			os_mut_release(s);
			numberToString(id+1,s);
			os_mut_release(s);

		}
		else{

			//HUNGRY

			numberToString(id+1,s);
			os_mut_request(s);
			numberToString(id,s);
			os_mut_request(s);
			
			//EATING

			eat();

			numberToString(id+1,s);
			os_mut_release(s);
			numberToString(id,s);
			os_mut_release(s);

		}
		think(random());
	}
	//DONE
}

void diph(){
	
	printf("DIPH\n");

	philos = N ;

    int i;

    for(i=0;i<philos;i++){
    	char * s;
    	numberToString(i,s);
    	os_mut_create(s);
    }

    for(i=0;i<philos;i++){
    	philosophers[i] = os_addProcess(&philosopher,1,'c',PCB_BACKGROUND,4000);
    }

    //IMPRIMIR

    //CAMBIAR LA CANTIDAD DE FILOSOFOS EN RUNTIME
    
    for(i=0;i<philos;i++){
    	char * s;
    	numberToString(i,s);
    	os_mut_delete(s);
    }
}






