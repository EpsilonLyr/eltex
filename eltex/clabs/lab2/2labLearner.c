#include "2lab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct learner{
	char *name;
	int recordBookNumber;
	char *faculty;
	char *group;
};

int workWithLearnerWE(int edit, struct learner *learners, int size){
	struct learner *learner;
	int number = 0;
	char *str;
	learner = (struct learner*)calloc(1, sizeof(struct learner));
	printf("введите  recordBookNumber\n");
	scanf("%d", &number);
	learner -> recordBookNumber = number;
	printf("введите  name\n");
	str = (char*)calloc(ARRSIZE, sizeof(char));
	fgets(str, ARRSIZE, stdin);
	fgets(str, ARRSIZE, stdin);
	change(str);
	learner -> name = str;
	printf("введите  faculty\n");
	str = (char*)calloc(ARRSIZE, sizeof(char));
	fgets(str, ARRSIZE, stdin);
	change(str);
	learner -> faculty = str;
	printf("введите  group\n");
	str = (char*)calloc(ARRSIZE, sizeof(char));
	fgets(str, ARRSIZE, stdin);
	change(str);
	learner -> group = str;
	if(edit == WFLAG){
		*(learners + size) = *learner;
		size++;
	}
	else{
		*(learners + edit) = *learner;
	}
	return size;
	
}

int cmpLearnerRecordBookNumber(const void *x1, const void *x2){
	return ((*(struct learner *)x1).recordBookNumber - (*(struct learner *)x2).recordBookNumber);
}

int cmpLearnerName(const void *x1, const void *x2){
	return strcmp((*(struct learner *)x1).name, (*(struct learner *)x2).name);
}

int main(void) {
	int choice = 0;
	int number = 0;
	char *str;
	FILE *fp;
	struct learner *learners = (struct learner*)calloc(ARRSIZE, sizeof(struct learner));
	struct learner *learner;
	int size = 0;
	while(choice != 1){
		printf("введите 1, чтобы завершить работу с таблицей\n2 - чтобы ввести данные\n");
		printf("3 - чтобы сохранить данные в таблицу\n4 - чтобы загрузить таблицу\n5 - чтобы просмотреть таблицу\n");
		printf("6 - сортировка\n7 - удаление\n8 - редактирование\n");
		scanf("%d", &choice);
		switch(choice){
			case 2: 
				size = workWithLearnerWE(WFLAG, learners, size);
			break;
			case 3:
				if ((fp = fopen("workWithLearner.txt", "w")) == NULL){
				    	printf("Не удалось открыть файл");
				    	exit(1);
				  }
				  for(int i = 0; i < size; i++){
				  	fprintf(fp, "%d\n", learners[i].recordBookNumber);
				  	fprintf(fp, "%s\n", learners[i].name);
				  	fprintf(fp, "%s\n", learners[i].faculty);
				  	fprintf(fp, "%s\n", learners[i].group);
				  }
				  fclose(fp);
			break;
			case 5:
				for(int i = 0; i < size; i++){
				  	printf("%d ;", learners[i].recordBookNumber);
				  	printf("%s ;", learners[i].name);
				  	printf("%s ;", learners[i].faculty);
				  	printf("%s ;", learners[i].group);
				  	printf("\n");
				  }
			break;
			case 4:
				size = 0;
				if ((fp = fopen("workWithLearner.txt", "r")) == NULL){
				    	printf("Не удалось открыть файл");
				    	exit(1);
				}
				while (1){
					learner = (struct learner*)calloc(1, sizeof(struct learner));
					if(fscanf(fp,"%d",&number) == EOF){
						break;
					}
					learner -> recordBookNumber = number;
				      	str = (char*)calloc(ARRSIZE, sizeof(char));
					if(fscanf(fp,"%s",str) == EOF){
						break;
					}
					learner -> name = str;
					str = (char*)calloc(ARRSIZE, sizeof(char));
					if(fscanf(fp,"%s",str) == EOF){
						break;
					}
					learner -> faculty = str;
					str = (char*)calloc(ARRSIZE, sizeof(char));
					if(fscanf(fp,"%s",str) == EOF){
						break;
					}
					learner -> group = str;
					*(learners + size) = *learner;
					size++;
				}
				fclose(fp);
			break;
			case 6:
				number = 0;
				while(number != 1 && number != 2){
					printf("введите 1, чтобы отсортировать по номеру зачетной книги\n2 - по имени\n");
					scanf("%d", &number);
					switch(number){
						case 1:
							qsort(learners, size, sizeof(struct learner), cmpLearnerRecordBookNumber);
							break;
						case 2:
							qsort(learners, size, sizeof(struct learner), cmpLearnerName);
							break;
					}
				}
			break;
			case 7:
				printf("введите номер строки для удаления\n");
				scanf("%d", &number);
				if(number < size && number > -1){
						free(learners[number].name);
						free(learners[number].faculty);
						free(learners[number].group);
					for(int i = number; i < size - 1; i++){
						*(learners + i) = *(learners + i + 1);
					}
					size--;
				}
			break;
			case 8:
				printf("введите номер строки для редактирования\n");
				scanf("%d", &number);
				if(number < size && number > -1){
						free(learners[number].name);
						free(learners[number].faculty);
						free(learners[number].group);
						size = workWithLearnerWE(number, learners, size);
				}
				else{
					printf("\n неверный индекс\n");
				}
			break;
		}  
	}
	
	for(int i = 0; i < size; i++){
		free(learners[i].name);
		free(learners[i].faculty);
		free(learners[i].group);
	}
	free(learners);
}
