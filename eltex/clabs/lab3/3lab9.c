#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define ARRSIZE 100

void change(char *str){
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] == '\n'){
			str[i] = '\0';
			break;
		}
	}
}

int cmp2(const void *x1, const void *x2){
    	const char** a = (const char**) x1;
    	const char** b = (const char**) x2;
	return strcmp(*a, *b);
}

int cmp3(const void *x1, const void *x2){
    	const char*** a = (const char***) x1;
    	const char*** b = (const char***) x2;
	return strcmp(**a, **b);
}

int main(void){
	FILE *fp;
	int size1;
	int size2;
	int size3 = 0;
	char str[ARRSIZE];
	char *arr1;
	char **arr2;
	char ***arr3;
	int size2arr[100];
	arr3 = (char***)calloc(ARRSIZE, sizeof(char*));
	if ((fp = fopen("text.txt", "r")) == NULL){
		printf("Не удалось открыть файл");
		exit(1);
	}
	while(1){
		size2 = 0;
		if(fgets(str,ARRSIZE,fp) == NULL){
			break;
		}
		change(str);
		arr1 = (char*)calloc(ARRSIZE, sizeof(char));
		arr2 = (char**)calloc(ARRSIZE, sizeof(char*));
		size1 = 0;
		for(int i = 0; *(str + i) != '\0'; i++){
			if(isalpha(*(str + i)) || isdigit(*(str + i))){
				*(arr1 + size1) = *(str + i);
				size1++;
			}
			else{
				if(size1 >= 1){
					*(arr1 + size1) = '\0';
					*(arr2 + size2) = arr1; 
					size1 = 0;
					size2++;
					arr1 = (char*)calloc(ARRSIZE, sizeof(char));
				}
			}
		}
		if(size1 >= 1){
			*(arr1 + size1) = '\0';
			*(arr2 + size2) = arr1; 
			size2++;
		}
		qsort(arr2, size2, sizeof(char*), cmp2);
		*(size2arr + size3) = size2;
		*(arr2 + size2) = NULL;
		*(arr3 + size3) = arr2;
		size3++;
	}
	qsort(arr3, size3, sizeof(char*), cmp3);
	int j;
	for(int i = 0; i < size3; i++){
		j = 0;
		while(*(*(arr3 + i) + j) != NULL){
			printf("%s ", *(*(arr3 + i) + j));
			j++;
		}
		printf("\n");
	}
}
