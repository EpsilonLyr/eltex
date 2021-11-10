#include <stdio.h>
#include <stdlib.h>
#define N 5

struct queue{
	int **arrays;
	int size;
	int first;
	int last;
};


void init(struct queue *q){
	q -> size = 3;
	q -> arrays = (int**)calloc(q -> size, sizeof(int*));
	q -> first = 0;
	q -> last = 0;
}

void insert(struct queue *q, int element){
	int *arr;
	if(q -> last == q -> size * N){
		q -> size *= 2; 
		q -> arrays = (int**)realloc(q -> arrays, q -> size * sizeof(int*));
	}
	if(q -> last % N == 0){
		arr = (int*)calloc(N, sizeof(int));
		*(arr) = element;
		*(q -> arrays + (q -> last / N)) = arr;
		q -> last += 1;
	}
	else{
		arr = *(q -> arrays + (q -> last / N ));
		*(arr + (q -> last % N)) = element;
		q -> last += 1;
	}
}

int isEmpty(struct queue *q){
	if(q -> first >= q -> last){
		return 1;
	}
	return -1;
}

void removeElement(struct queue *q){
	int *arr;
	if(isEmpty(q) == 1){
		printf("очередь пуста\n");
	}
	else{
		q -> first += 1;
		if(q -> first % N == 0){
			arr = *(q -> arrays + (q -> first / N ) - 1);
			free(arr);
			arr = NULL;
		}
	}
}

void printQueue(struct queue *q){
	for(int i = q -> first; i < (q -> last); i++){
		printf("%d ", *(*(q -> arrays + (i / N )) + (i % N) )); 
	}
	printf("\n");
}

void deleteQueue(struct queue *q){
	for(int i = q -> first; i < (q -> last); i += N){
		free(*(q -> arrays + (i / N ))); 
	}
	free(q);
	q = NULL;
}

int main(void){
	int amount = 0;
	struct queue *q = (struct queue*)calloc(1, sizeof(struct queue));
	init(q);
	for(int i = 0; i < 25; i++){
		insert(q, i);
	}
	printQueue(q);
	removeElement(q);
	printQueue(q);
	for(int i = 0; i < 6; i++){
		removeElement(q);
	}
	printQueue(q);
	deleteQueue(q);
}
