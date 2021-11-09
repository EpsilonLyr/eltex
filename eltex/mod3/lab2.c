#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

off_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}

int main(){
	FILE *fp;
	int i = 0;
	off_t size = fsize("lab2.c");
	printf("\n%ld\n", fsize("lab2.c"));
	if ((fp = fopen("lab2.c", "r")) == NULL){
	    	printf("Не удалось открыть файл");
	 	exit(1);
	}
	char arr[size];
	char *array;
	int shmid;
	char pathname[] = "lab2.c";
	key_t key; 
	if((key = ftok(pathname,0)) < 0){
		printf("Can\'t generate key\n");
		exit(-1);
	}
	if((shmid = shmget(key, size, 0666|IPC_CREAT|IPC_EXCL)) < 0){


		printf("Can\'t create shared memory\n");
		exit(-1);
	}
	if((array = (char *)shmat(shmid, NULL, 0)) == (void *)(-1)){
		printf("Can't attach shared memory\n");
		exit(-1);
	}

	while ((arr[i] = fgetc(fp)) != EOF) {
        	array[i] = arr[i];
        	i++;
    	}
	return 0;
} 
