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
	off_t size = fsize("lab2.c");
	printf("\n%ld\n", fsize("lab2.c"));
	char *array;
	int shmid;
	int new = 1;
	char pathname[] = "lab2.c"; 
	key_t key;
	if((key = ftok(pathname,0)) < 0){
		printf("Can\'t generate key\n");
		exit(-1);
	}

	if((shmid = shmget(key, size, 0)) < 0){
		printf("Can\'t find shared memory\n");
		exit(-1);
	}

	if((array = (char *)shmat(shmid, NULL, 0)) == (void *)(-1)){
		printf("Can't attach shared memory\n");
		exit(-1);
	}
	for(int i = 0; i < size -1; i++){
		printf("%c", array[i]);
	}

	if(shmdt(array) < 0){
		printf("Can't detach shared memory\n");
		exit(-1);
	}
	return 0;
} 
