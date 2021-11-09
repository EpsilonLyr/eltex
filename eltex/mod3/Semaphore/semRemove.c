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


int main(void){
	key_t key;
	int semid;
	union semun arg;
	char pathname[] = "semInit.c";

	if ((key = ftok(pathname, 0)) == -1){ 
		printf("Can\'t generate key\n");
		exit(-1);
	}

	if ((semid = semget(key, 1, 0)) == -1) {
		printf("Can\'t get semid\n");
		exit(-1);
	}

	if (semctl(semid, 0, IPC_RMID, arg) == -1) {
		perror("semctl");
		exit(1); 
	}
	return 0;
}
