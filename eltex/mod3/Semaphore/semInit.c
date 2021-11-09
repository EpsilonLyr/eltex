#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short  *array;
};



int main(){
	int semid; 
	union semun arg;
	char pathname[] = "semInit.c"; 
	key_t key; 

	struct sembuf mybuf;


	if((key = ftok(pathname,0)) < 0){
		printf("Can\'t generate key\n");
		exit(-1);
	}


	if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0){
		printf("Can\'t get semid\n");
		exit(-1);
	}

    	arg.val = 1;

    	if(semctl(semid, 0, SETVAL, arg) < 0) {
		perror("semctl");
		 exit(12);
	}

	return 0;
} 
