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

long int count; //////////////////////////////////////////////////////////


pthread_barrier_t barrier;
pthread_mutex_t mutex;

void sig_usr(int signo){
 	printf("%ld received signal of the need to die\n", pthread_self());
	pthread_exit(NULL);
}

void *hungerGames(void *arg){
	int status;
	FILE *fp = (FILE *) arg;
	pthread_mutex_lock(&mutex);
	fprintf(fp, "%ld\n", pthread_self());
	printf("%ld prepared\n", pthread_self());
	fflush(fp);
	pthread_mutex_unlock(&mutex); 	
	status = pthread_barrier_wait(&barrier);
	if (status == PTHREAD_BARRIER_SERIAL_THREAD) {
		pthread_barrier_destroy(&barrier);
	} else if (status != 0) {
		perror("barrier_destroy");
		pthread_exit(NULL);
	}
	printf("%ld overcame the barrier\n", pthread_self());
	int strings;
	long int enemy;
	long int enemies[count];
	int target;
	while(1){
		strings = 0;
		pthread_mutex_lock(&mutex);
		printf("%ld lock mutex\n", pthread_self());		
		fseek(fp, 0, SEEK_SET);
		for(int j = 0; !feof(fp) && !ferror(fp); j++){
			if(0 < fscanf(fp, "%ld", &enemy)){
				if(enemy != pthread_self()){
					enemies[strings] = enemy;
					strings++;
				}
			}
		}
		if(strings == 0){
			pthread_mutex_unlock(&mutex); 
			pthread_exit(NULL);
		}
		target = rand() % strings;
		fseek(fp, 0, SEEK_SET);
		if ((fp = fopen("pids.txt", "w+")) == NULL){
		    	printf("Не удалось открыть файл");
		    	exit(1);
		}
		for(int j = 0; j < strings; j++) {
			if(j != target){
				fprintf(fp, "%ld\n", enemies[j]);
				fflush(fp);
			}
		}
		fprintf(fp, "%ld\n", pthread_self());
		fclose(fp);
		printf("%ld killed by %ld\n", enemies[target], pthread_self());
		pthread_kill(enemies[target], SIGUSR1);
		printf("%ld unlock mutex\n", pthread_self());
		pthread_mutex_unlock(&mutex); 
	}
	
	
	pthread_exit(NULL);
}



int main(int argc, char* argv[]){
	if(argc != 2){
		printf("введите количество дочерних процессов\n");
		exit(-1);
	}
	
	FILE *fp;
	if ((fp = fopen("pids.txt", "w+")) == NULL){
	    	printf("Не удалось открыть файл\n");
	    	exit(1);
	}
	
	count = strtol(argv[1], NULL, 10);
	pthread_t threads[count];
	

	struct sigaction sa_usr;
	sa_usr.sa_flags = 0;
	sa_usr.sa_handler = sig_usr;
    
    	sigaction(SIGUSR1, &sa_usr, NULL);
    	sigaction(SIGUSR2, &sa_usr, NULL);
	
	
	int i = 0;
	if(0 != pthread_barrier_init(&barrier, NULL, count)){
		perror("barrier init");
		exit(-1);
	}
	if(0 != pthread_mutex_init(&mutex, NULL)){
		perror("mutex init");
		exit(-1);
	}
	for (i = 0; i < count; i++) {
    	    if( 0 != pthread_create(&threads[i], NULL, hungerGames, fp)){
    	    	perror("create");
    	    	exit(-1);
    	    }
    	}

    	for (i = 0; i < count; i++) {
        	pthread_join(threads[i], NULL);
    	}
    	long int enemy;
	if(0 < fscanf(fp, "%ld", &enemy)){
		printf("%ld is survived\n", enemy);	
	}
    	fclose(fp);
    	pthread_mutex_destroy(&mutex);
    
	
}
