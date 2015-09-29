//To compile in cmd line: gcc -std=c99 cpu.c
//To run after compiling: a
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#define ID_LEN 8
#define isCount 10
#define RegAmount 2
#define ProcAmount 8

int CPURegisters[RegAmount] = {};
char *IS[isCount];
FILE *f;

/*------------------------------------------------------------------
 * Function:     printMemory
 * Purpose:      prints all positions and values of memory array
 * Input args:   int *pointer: pointer to beginning position of memory
				 
 * Return val:   void
 */
void printMemory(int *pointer){
	fprintf(f, "Memory Array:\n");
	int *i,j;
	for(j=0, i=pointer; j<5; i++,j++)
		fprintf(f, "Position=%d\tValue=%d\n",i,*i);
	fprintf(f,"\n");
}

/*------------------------------------------------------------------
 * Function:     printRegisters
 * Purpose:      prints all positions and values of register array
 * Input args:   int *pointer: pointer to beginning position of memory
				 
 * Return val:   void
 */
void printRegisters(int RegArray[]){
	fprintf(f,"Register Values:\n");
	for(int i = 0; i < sizeof(RegArray)/sizeof(int); i++){
		fprintf(f,"Register %i: %i\n",i,RegArray[i]);
	}
	fprintf(f,"\n");
}

/*------------------------------------------------------------------
 * Function:     createIS
 * Purpose:      save abbreviations of instructions in an array and copy to memory array
 * Input args:   
 * Return val:   void
 */
 
/****   WORK IN PROGRESS      ***/
void createIS(){
	fprintf(f,"Entering createIS\n");
	const char *temp[] = {};
	temp[0] = "NULL";
	temp[1] = "FE 03 01";
	temp[2] = "ST 01 02";
	temp[3] = "SU 03 02";
	temp[4] = "CO 03 01";
	temp[5] = "MU 02 02";
	temp[6] = "GZ 10";
	temp[7] = "LZ 5";
	temp[8] = "EV 6";
	temp[9] = "OD 7";
	for (int j = 0; j < isCount; j++){
		fprintf(f,"Loop: %i\n",j);
		IS[j] = malloc((ID_LEN+1) * sizeof(char*));
		fprintf(f,"Loop: %i",j);
		/**
			This is the part where it freezes
			We just need to copy each item in temp into each memory position in IS
		**/
		strcpy(IS[j], temp[j]);
		fprintf(f,"Finished loop %i",j);
	}
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
	fprintf(f,"Fetching data from Position %i in Memory and storing it in Register %i\n",SrcPtr,RegPos);
	int *i = pointer;
	for(int j=0; j<SrcPtr; j++)
		i++;
	CPURegisters[RegPos] = *i;
	fprintf(f,"\n");
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
	fprintf(f,"Fetching data from Register %i and storing it in Position %i in Memory\n\n",RegPos,DesPtr);
	int *i = pointer;
	for(int j=0; j<DesPtr; j++)
		i++;
	*i = CPURegisters[RegPos];
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

struct process{
	int id;
	int state;
	int priority;
	int *stackPtr;
	int *basePtr;
	int PC;
	int RegArray[RegAmount];
};

/*------------------------------------------------------------------
 * Function:     randomize
 * Purpose:      randomize all values of processes starting from process 2 (Process 0 = null process, Process 1 = current process)
 * Input args:   
 * Return val:   void
 */
void randomize(struct process *Processes){
	/**
		Intializing all other processes to random stats
	**/
	fprintf(f,"Now randomizing values of Processes\n");
	srand(time(NULL));
	for(int i = 2; i < ProcAmount; i++){
		Processes[i].id = i;
		int temp = rand() % 6 + 1;
		Processes[i].state = temp;
		temp = rand() % 6 + 1;
		Processes[i].priority = temp;
		Processes[i].basePtr = malloc(sizeof(int)*2);
		Processes[i].stackPtr = Processes[i].basePtr;
		Processes[i].PC = 1;
		for(int j = 0; j < RegAmount; j++){
			temp = rand() % 6 + 1;
			Processes[i].RegArray[j] = temp;
		}
	}
}

/*------------------------------------------------------------------
 * Function:     createProcesses
 * Purpose:      Sets initial values of all processes
				Process 0 = null process, does not fulfill any instructions
				Process 1 = Current Process; used for context switching
 * Input args:   
 * Return val:   void
 */
void createProcesses(struct process *Processes){
	Processes[0].id = 0;
	Processes[0].state = 0;
	Processes[0].priority = 0;
	Processes[0].basePtr = malloc(sizeof(int)*2);
	Processes[0].stackPtr = Processes[0].basePtr;
	Processes[0].PC = 0;
	
	/**
		Current Process
		This is used to print during instructions, set to Null Process on startup
	**/
	Processes[1].id = 1;
	Processes[1].state = Processes[0].state;
	Processes[1].priority = Processes[0].priority;
	Processes[1].basePtr = Processes[0].basePtr;
	Processes[1].stackPtr = Processes[0].stackPtr;
	Processes[1].PC = Processes[0].PC;
}

/*------------------------------------------------------------------
 * Function:     findNext
 * Purpose:      finds process with highest priority and returns position in Processes
 * Input args:  
 * Return val:   next: position of highest priority Process in Processes
 */
int findNext(struct process *Processes){
	fprintf(f,"Finding highest priority Process\n");
	int next, highest = 0; 
	for(int i = 2; i < ProcAmount; i++){
		if(Processes[i].priority > highest){
			highest = Processes[i].priority;
			next = i;
		}
	}
	return next;
}

/*------------------------------------------------------------------
 * Function:     setNext
 * Purpose:      sets all values of Process 1 (current process) to next process
 * Input args:   int next = position of next process 
 * Return val:   void
 */
void setNext(struct process *Processes, int next){
	fprintf(f,"Replacing current Process values with highest priority Process values\n\n");
	Processes[1].id = Processes[next].id;
	Processes[1].state = Processes[next].state;
	Processes[1].priority = Processes[next].priority;
	Processes[1].basePtr = Processes[next].basePtr;
	Processes[1].stackPtr = Processes[next].stackPtr;
	Processes[1].PC = Processes[next].PC;
	for(int i = 0; i < RegAmount; i++){
		Processes[1].RegArray[i] = Processes[next].RegArray[i];
	}
}

/*------------------------------------------------------------------
 * Function:     printCurrent
 * Purpose:     prints all values of current process
 * Input args:  
 * Return val:   void
 */
void printCurrent(struct process *Processes){
	fprintf(f,"====\nCurrent Process\n====\n");
	fprintf(f,"Current Process ID: %i\n",Processes[1].id);
	fprintf(f,"Current Process Priority: %i\n",Processes[1].priority);
	fprintf(f,"Current Process BasePtr: %i\n",Processes[1].basePtr);
	fprintf(f,"Current Process StackPtr: %i\n",Processes[1].stackPtr);
	fprintf(f,"Current Process PC: %i\n",Processes[1].PC);
	fprintf(f,"Current Process Registers: \n");
	printRegisters(Processes[1].RegArray);
}

/*------------------------------------------------------------------
 * Function:     printAllProcesses
 * Purpose:     prints all values of all Processes
 * Input args:  
 * Return val:   void
 */
void printAllProcesses(struct process *Processes){
	for(int i = 0; i < ProcAmount; i++){ 
		if(i == 0){
			fprintf(f,"====\nNull Process\n====\n");
		}
		else if(i == 1){
			fprintf(f,"====\nCurrent Process\n====\n");
		}
		fprintf(f,"Process ID: %i\n",Processes[i].id);
		fprintf(f,"Process Priority: %i\n",Processes[i].priority);
		fprintf(f,"Process BasePtr: %i\n",Processes[i].basePtr);
		fprintf(f,"Process StackPtr: %i\n",Processes[i].stackPtr);
		fprintf(f,"Process PC: %i\n",Processes[i].PC);
		fprintf(f,"Process Registers: \n");
		printRegisters(Processes[1].RegArray);
	}
}

void createQueue(struct process *Processes){
	int temp = [];
	for(int i = 0; i < ProcAmount; i++){ 
		
	}
}

void example(struct process *Processes){
	//Process values are already set to random. Can start randomized time demo here 
	printCurrent(Processes);
	setNext(Processes, findNext(Processes));
	printCurrent(Processes);
}

int main()
{
	int *pointer = malloc(sizeof(int) * 5);
	f = fopen("output.txt", "w");
	//createIS();
	struct process Processes[ProcAmount];
	createProcesses(Processes);
	randomize(Processes);
	printAllProcesses(Processes);
	
	example(Processes);
	
	
	//Freeing all allocated memory
	for(int i = 0; i < ProcAmount; i++){ free(Processes[i].basePtr); }
	for(int i = 0; i < isCount; i++){ free(IS[i]); }
	free(pointer);
	return 0;
}

