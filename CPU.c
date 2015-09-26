//To run in cmd line: gcc -std=c99 cpu.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

//For simplicity, I'm only creating 2 registers; more will be created once the CPU becomes more complex
int RegArray[2] = {};
int ProcAmount = 6;

/*------------------------------------------------------------------
 * Function:     printMemory
 * Purpose:      prints all positions and values of memory array
 * Input args:   int *pointer: pointer to beginning position of memory
				 
 * Return val:   void
 */
void printMemory(int *pointer){
	printf("Memory Array:\n");
	int *i,j;
	for(j=0, i=pointer; j<5; i++,j++)
		printf("Position=%d\tValue=%d\n",i,*i);
	printf("\n");
}

/*------------------------------------------------------------------
 * Function:     printRegisters
 * Purpose:      prints all positions and values of register array
 * Input args:   int *pointer: pointer to beginning position of memory
				 
 * Return val:   void
 */
void printRegisters(){
	printf("Register Values:\n");
	for(int i = 0; i < sizeof(RegArray)/sizeof(int); i++){
		printf("Register %i: %i\n",i,RegArray[i]);
	}
	printf("\n");
}

/*------------------------------------------------------------------
 * Function:     fetch
 * Purpose:      retrieves value inside memory and stores it in a register
 * Input args:   int *pointer: pointer to beginning position of memory
				 int SrcPtr: position in memory array to be fetched
				 int RegPos: position of register in register array
				 
 * Return val:   void
 */
void fetch(int *pointer, int SrcPtr, int RegPos){
	printf("Fetching data from Position %i in Memory and storing it in Register %i\n",SrcPtr,RegPos);
	int *i = pointer;
	for(int j=0; j<SrcPtr; j++)
		i++;
	RegArray[RegPos] = *i;
	printf("\n");
}

/*------------------------------------------------------------------
 * Function:     store
 * Purpose:      retrieves value inside register and stores it in memory
 * Input args:   int *pointer: pointer to beginning position of memory
				 int RegPos: position of register in register array
				 int DesPtr: position in memory array to store value
				 
 * Return val:   void
 */
void store(int *pointer, int RegPos, int DesPtr){
	printf("Fetching data from Register %i and storing it in Position %i in Memory\n\n",RegPos,DesPtr);
	int *i = pointer;
	for(int j=0; j<DesPtr; j++)
		i++;
	*i = RegArray[RegPos];
}

int add(int a,int b){
	return a + b;
}

int subtract(int a, int b){
	return a - b;
}

int compare(int a,int b){
	return a > b;
}

int multiply(int a, int b){
	return a*b;
}

int greaterThanZero(int a){
	return a > 0;
}

int lessThanZero(int a){
	return a < 0;
}

int isEven(int a){
	return a%2==0;
}

int isOdd(int a){
	return a%2==1;
}

/*------------------------------------------------------------------
 * Function:     fetchExample
 * Purpose:      displays sample uses of fetch function
 * Input args:   int *pointer: pointer to beginning position of memory
				 
 * Return val:   void
 */
void fetchExample(int *pointer){
	printMemory(pointer);
	printRegisters();
	fetch(pointer, 0, 1);
	printMemory(pointer);
	printRegisters();
	fetch(pointer, 1, 0);
	printMemory(pointer);
	printRegisters();
}

/*------------------------------------------------------------------
 * Function:     storeExample
 * Purpose:      displays sample uses of store function 
 * Input args:   int *pointer: pointer to beginning position of memory
				 
 * Return val:   void
 */
void storeExample(int *pointer){
	printMemory(pointer);
	printRegisters();
	store(pointer, 1, 3);
	printMemory(pointer);
	printRegisters();
	store(pointer, 0, 4);
	printMemory(pointer);
	printRegisters();
}

/*
 * Function:    nullProcess
 * Purpose:     runs a null process so the scheduler is always busy
 */
void nullProcess(){
    while(1)
        ;// do nothing
}

struct process{
	int id;
	int state;
	int priority;
	int *stackPtr;
	int *basePtr;
};

/**
Don't worry about this function. I was just messing around with stuff.
**/
struct process *processCreate(){
	struct process *who;
	//who = malloc(sizeof(struct process));
	*who.id = 1;
	int temp = rand() % 6 + 1;
	who.state = temp;
	temp = rand() % 10 + 1;
	who.priority = temp;
	return who;
}


void createProcesses(struct process *Processes){
	srand(time(NULL));
	for(int i = 0; i < ProcAmount; i++){
		Processes[i].id = i+1;
		int temp = rand() % 6 + 1;
		Processes[i].state = temp;
		temp = temp = rand() % 6 + 1;
		Processes[i].priority = temp;
		Processes[i].basePtr = malloc(sizeof(int)*2);
		Processes[i].stackPtr = Processes[i].basePtr;
	}
	printf("State: %d\n",Processes[5].state);
	printf("Priority: %d\n",Processes[5].priority);
	printf("Stack: %d\n",Processes[5].stackPtr);
	printf("Base: %d\n",Processes[5].basePtr);
	
}


int main()
{
	int *pointer = malloc(sizeof(int) * 5);
	fetchExample(pointer);
	storeExample(pointer);
	struct process Processes[ProcAmount];
	//createProcesses(Processes);
	struct process p1 = processCreate();
	printf("%d",p1.id);
	free(p1);
	free(pointer);
	return 0;
}

