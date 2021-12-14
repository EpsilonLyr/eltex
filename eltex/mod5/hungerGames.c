#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>

#define STACK_MAX_SIZE 100


typedef struct Stack_tag {
    long int data[STACK_MAX_SIZE];
    size_t size;
} Stack_t;


void killEnemy(int numberOfEnemies, long int *enemies);
int defineEnemies(long int *enemies);
int pop(Stack_t *stack, long int *value);
int push(Stack_t *stack, const long int value);
void initStack();
void waitAtBarrier();
void *hungerGames(void *arg);

Stack_t stack;
pthread_barrier_t barrier;
pthread_mutex_t mutex;

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("введите количество дочерних процессов\n");
		exit(-1);
	}
	stack.size = 0;
	
	long int count = strtol(argv[1], NULL, 10);
	pthread_t threads[count];
	
	
	if(0 != pthread_barrier_init(&barrier, NULL, count)){
		perror("barrier init");
		exit(-1);
	}
	if(0 != pthread_mutex_init(&mutex, NULL)){
		perror("mutex init");
		exit(-1);
	}
	
	for (int i = 0; i < count; i++) {
    	    if( 0 != pthread_create(&threads[i], NULL, hungerGames, &count)){
    	    	perror("create");
    	    	exit(-1);
    	    }
    	}

    	for (int i = 0; i < count; i++) {
        	pthread_join(threads[i], NULL);
    	}
    	long int winner = 0;
    	pop(&stack, &winner);
    	printf("%ld won\n", winner);
    	pthread_mutex_destroy(&mutex);
    
	
}

int push(Stack_t *stack, const long int value) {
    if (stack->size >= STACK_MAX_SIZE) {
        return -1;
    }
    stack->data[stack->size] = value;
    stack->size++;
    return 0;
}

int pop(Stack_t *stack, long int *value) {
    if (stack->size == 0) {
        return -1;
    }
    stack->size--;
    *value = stack->data[stack->size];
    return 0;
}


int defineEnemies(long int *enemies){
	long int enemy;
	int numberOfStrings = 0;
	while(-1 != pop(&stack, &enemy)){
		if(enemy != pthread_self()){
			enemies[numberOfStrings] = enemy;
			numberOfStrings++;
		}
	}
	return numberOfStrings;
}

void killEnemy(int numberOfEnemies, long int *enemies){
	long int target = rand() % numberOfEnemies;
	for(int j = 0; j < numberOfEnemies; j++) {
		if(j != target){
			push(&stack, enemies[j]);
		}
	}
	push(&stack, pthread_self());
	printf("%ld killed by %ld\n", enemies[target], pthread_self());
	pthread_cancel(enemies[target]);
}

void initStack(){
	pthread_mutex_lock(&mutex);
	push(&stack, pthread_self());
	printf("%ld prepared\n", pthread_self());
	pthread_mutex_unlock(&mutex);
}

void waitAtBarrier(){
	int status;
	status = pthread_barrier_wait(&barrier);
	if (status == PTHREAD_BARRIER_SERIAL_THREAD) {
		pthread_barrier_destroy(&barrier);
	} else if (status != 0) {
		perror("barrier_destroy");
		pthread_exit(NULL);
	}
}

void *hungerGames(void *arg){
	long int count = *(long int*) arg;
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	
	initStack();	
	waitAtBarrier();
	printf("%ld overcame the barrier\n", pthread_self());
	
	int numberOfEnemies;
	long int enemies[count];
	while(1){
		pthread_mutex_lock(&mutex);
		printf("%ld lock mutex\n", pthread_self());	
		
		numberOfEnemies = defineEnemies(enemies);
		
		if(numberOfEnemies == 0){
			push(&stack, pthread_self());
			printf("%ld unlock mutex\n", pthread_self());
			pthread_mutex_unlock(&mutex); 
			pthread_exit(NULL);
		}
		
		killEnemy(numberOfEnemies, enemies);
		printf("%ld unlock mutex\n", pthread_self());
		pthread_mutex_unlock(&mutex); 
	}
}

