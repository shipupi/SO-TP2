#include "include/syscalls.h"
#include "include/PCB.h"
#include "include/applications.h"
#include "include/memory.h"
#include "include/stdio.h"


#define INACTIVE 0
#define HUNGRY 1
#define EATING 2
#define THINKING 3
#define MAXFILOS 100
#define IDMUT "ID_MUTEX"
#define PRINTMUT "PRINT_MUTEX"




uint64_t random(){
	// Entre 2 y 12
	uint64_t t = os_ticks();
	uint64_t p = os_pid();
	return (((t+p) * (t-p) * (t-p)*31*17*11*13 *37)%15) + 4;
}

typedef struct Philo
{
	int state;
	int pid;
}Philo;

typedef struct Fork
{
	char mut[3];
}Fork;

static char states[4] = {'I','H','E','T'};
static Philo filosofos[MAXFILOS];
static Fork cubiertos[MAXFILOS];
static int activos = 0;

void print_state(){
	int i,j;
	if(activos < 3) return;

	int maxJ = ((activos-1) / 4) + 3;
	int maxI = ((activos-3) / 4) + 3;
	int current = 0;
	char matrix[maxI][maxJ + 1];
	for (i = 0; i < maxI; ++i)
	{
		for (j = 0; j <= maxJ; ++j)
		{
			if(j == maxJ) {
				matrix[i][j] = 0;
			} else {
				matrix[i][j] = ' ';
			}
		}
	}
	for (i= 1; i < ((activos-1) / 4) + 2; ++i)
	{
		if(current < activos) {
			// matrix[0][i] = current+ '0';
			matrix[0][i] = states[filosofos[current].state];
			current++;
		}
	}
	for (i = 1; i < ((activos -3) / 4) + 2; ++i)
	{
		if(current < activos) {
			// matrix[i][maxJ - 1] = current + '0';
			matrix[i][maxJ - 1] = states[filosofos[current].state];
			current++;
		}
	}
	for (i = 1; i < ((activos -2) / 4) + 2; ++i)
	{
		if(current < activos) {
			// matrix[maxI - 1][maxJ - 1 - i] = current+ '0';
			matrix[maxI - 1][maxJ - 1 - i] = states[filosofos[current].state];
			current++;
		}
	}
	for (i = 1; i < ((activos - 4) / 4) + 2; ++i)
	{
		if(current < activos) {				
			// matrix[maxI - 1 - i][0] = current+ '0';
			matrix[maxI - 1 - i][0] = states[filosofos[current].state];
			current++;
		}
	}

	for (int i = 0; i < maxI; ++i)
	{
		printf(matrix[i]);
		printf("\n");
	}
	printf("\n");
	printf("\n");
}

void think(int myId) {
	int n = random();
	printf("Filosofo "); pint(myId);printf(" pensando por ");pint(n); printf(" segundos\n");
	filosofos[myId].state = THINKING;
	os_sleep_seconds(n);
}

void eat(int myId) {
	int n = random();
	printf("Filosofo "); pint(myId);printf(" comiendo por ");pint(n); printf(" segundos\n");
	filosofos[myId].state = EATING;
	os_sleep_seconds(n);
}


int getId() {
	os_mut_request(IDMUT);
	int toreturn = activos;
	activos++;
	os_mut_release(IDMUT);	
	return toreturn;
}


void philosopher(){

	printf("Filosofo creado! Id: ");
	int id = getId();
	pint(id);printf("\n");

	char requestRight[3];
	char requestLeft[3];
	// think
	while(1) {

		think(id);
		filosofos[id].state = HUNGRY;

		// get forks
		if(id % 2 == 0){
			//wait right fork then left
			// printf("filosofo: ");pint(id);printf(" pidiendo mutex: "); printf(cubiertos[(id + 1) % activos].mut); printf("\n");
			printf("filosofo: ");pint(id);printf(" esta hambriento\n");
			memcopy(requestRight, cubiertos[(id + 1) % activos].mut, 3);
			os_mut_request(requestRight);
			// printf("filosofo: ");pint(id);printf(" pidiendo mutex: "); printf(cubiertos[id].mut);printf("\n");
			memcopy(requestLeft, cubiertos[id].mut, 3);
			os_mut_request(requestLeft);
		} else {
			// printf("filosofo: ");pint(id);printf(" pidiendo mutex: "); printf(cubiertos[id].mut);printf("\n");
			printf("filosofo: ");pint(id);printf(" esta hambriento\n");
			// printf("filosofo: ");pint(id);printf(" pidiendo mutex: "); printf(cubiertos[id].mut);printf("\n");
			memcopy(requestLeft, cubiertos[id].mut, 3);
			os_mut_request(requestLeft);
			// printf("filosofo: ");pint(id);printf(" pidiendo mutex: "); printf(cubiertos[(id + 1) % activos].mut);printf("\n");	
			memcopy(requestRight, cubiertos[(id + 1) % activos].mut, 3);
			os_mut_request(requestRight);
		}
		eat(id);
		// printf("filosofo: ");pint(id);printf(" largando mutex: "); printf(cubiertos[id].mut);printf("\n");	
		os_mut_release(requestRight);
		// printf("filosofo: ");pint(id);printf(" largando mutex: "); printf(cubiertos[(id + 1) % activos].mut);printf("\n");	
		os_mut_release(requestLeft);
	}
	
}

void addStartingPhilosophers(int toAdd) {
	for (int i = 0; i < toAdd; ++i)
	{
		cubiertos[i].mut[0] = i >= 10? '1': '0';
		cubiertos[i].mut[1] = i % 10+'0';
		cubiertos[i].mut[2] = 0;
		os_mut_create(cubiertos[i].mut);
		os_addProcess(&philosopher,1, PCB_BACKGROUND, 4000, INVALID_FD, SPLIT_FD);
	}
}

void printInstructions() {
	printf("Bienvenido a los filosofos hambrientos\n");

	printf("En la pantalla derecha se ven las acciones\n");
	printf("de los distintos filosofos\n\n");
	printf("Por defecto se empieza con 4 filosofos\n\n");
	printf("Comandos:\n");
	printf("  p: imprimir estado\n");
	printf("  a: agregar filosofo (max: 20)\n");
	printf("  r: agregar filosofo (min: 3)\n");

	printf("Estados: \n");
	printf("T: Thinking\n");
	printf("H: Hungry\n");
	printf("E: Eating\n");
}

void initialize() {
	os_mut_create(IDMUT);
	os_mut_create(PRINTMUT);
	if(!isSplit()) {
		os_addProcess(&split,1,PCB_BACKGROUND, 4000, INVALID_FD, SPLIT_FD);
		os_sleep_seconds(1);
	}
}

void addPhilo() {
	if (activos == 9){
		printf("No soporta mas filosofos\n");
	}else{
	cubiertos[activos].mut[0] = activos >= 10? '1': '0';
	cubiertos[activos].mut[1] = activos % 10+'0';
	cubiertos[activos].mut[2] = 0;
	os_mut_create(cubiertos[activos].mut);
	filosofos[activos].state = INACTIVE;
	int p = os_addProcess(&philosopher,1, PCB_BACKGROUND, 4000, INVALID_FD, SPLIT_FD);
	filosofos[activos].pid = p;
	}
}
void removePhilo() {
	if(activos == 3 ){
		printf("no se puden eliminar");
		printf("\n");
		printf("solo quedan 3 filosofos");
		printf("\n");
	}
	if(activos != 3){
		printf("waiting to be able to remove\n");
		int trying = 1;
		while(trying){
			if(filosofos[activos-1].state ==THINKING ){
				os_kill(filosofos[activos-1].pid);
				activos--;
				trying = 0;
			}
		}
	}

}

void filo(){

	activos = 0;	

	// PCB* p = os_requestMemorySpace(sizeof(PCB));
	// os_pstat(p);
	initialize();


	printInstructions();

	addStartingPhilosophers(3);


	// os_freeMemorySpace(p, sizeof(PCB));
	char c;

	while ((c = getChar()) != 'q') {
		if (c == 'a') {
			// printf("add filosofer\n");
			addPhilo();
		} else if(c == 'r') {
			removePhilo();
			// printf("remove filosofer\n");
		} else if(c == 'p') {

			print_state();
					}
	}
}

