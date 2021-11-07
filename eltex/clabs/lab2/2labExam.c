#include "2lab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



struct exam{
	char *examName;
	time_t date;
	char *professorName;
	int amount;
	int *marks;
};

int workWithExamWE(int edit, struct exam *exams, int size){
	struct exam *exam;
	int number = 0;
	char *str;
	int *marks;
	exam = (struct exam*)calloc(1, sizeof(struct exam));
	printf("введите  amount\n");
	scanf("%d", &number);
	exam -> amount = number;
	marks = (int*)calloc(ARRSIZE, sizeof(int));
	for(int i = 0; i < exam -> amount; i++){
		printf("введите  mark\n");
		scanf("%d", &number);
		*(marks + i) = number;
	}
	exam -> marks = marks;
	printf("введите  examName\n");
	str = (char*)calloc(ARRSIZE, sizeof(char));
	fgets(str, ARRSIZE, stdin);
	fgets(str, ARRSIZE, stdin);
	change(str);
	exam -> examName = str;
	exam -> date = time(NULL);
	printf("введите  professorName\n");
	str = (char*)calloc(ARRSIZE, sizeof(char));
	fgets(str, ARRSIZE, stdin);
	change(str);
	exam -> professorName = str;
	if(edit == WFLAG){
		*(exams + size) = *exam;
		size++;
	}
	else{
		*(exams + edit) = *exam;
	}
	return size;
}

int cmpExamAmount(const void *x1, const void *x2){
	return ((*(struct exam *)x1).amount - (*(struct exam *)x2).amount);
}

int cmpExamName(const void *x1, const void *x2){
	return strcmp((*(struct exam *)x1).examName, (*(struct exam *)x2).examName);
}

int main(void) {
	int choice = 0;
	int number = 0;
	time_t time = 0;
	int *marks;
	char *str;
	FILE *fp;
	int size = 0;
	struct exam *exams = (struct exam*)calloc(ARRSIZE, sizeof(struct exam));
	struct exam *exam;
	while(choice != 1){
		printf("введите 1, чтобы завершить работу с таблицей\n2 - чтобы ввести данные\n");
		printf("3 - чтобы сохранить данные в таблицу\n4 - чтобы загрузить таблицу\n5 - чтобы просмотреть таблицу\n");
		printf("6 - сортировка\n7 - удаление\n8 - редактирование\n");
		scanf("%d", &choice);
		switch(choice){
			case 2:
				size = workWithExamWE(WFLAG, exams, size);
			break;
			case 3:
				if ((fp = fopen("workWithExam.txt", "w")) == NULL){
				    	printf("Не удалось открыть файл");
				    	exit(1);
				  }
				  for(int i = 0; i < size; i++){
				  	fprintf(fp, "%d\n", exams[i].amount);
				  	for(int j = 0; j < exams[i].amount; j++){
				  		fprintf(fp, "%d\n", exams[i].marks[j]);	
				  	}
				  	fprintf(fp, "%s\n", exams[i].examName);
				  	fprintf(fp, "%ld\n", exams[i].date);
				  	fprintf(fp, "%s\n", exams[i].professorName);
				  }
				  fclose(fp);

			break;
			case 5:
				for(int i = 0; i < size; i++){
				  	printf("%d ;", exams[i].amount);
				  	for(int j = 0; j < exams[i].amount; j++){
				  		printf("%d ", exams[i].marks[j]);	
				  	}
				  	printf(" ;");
				  	printf("%s ;", exams[i].examName);
				  	printf("%s ;", exams[i].professorName);
				  	printf("%s", ctime(&(exams[i].date)));
				  	printf("\n");
				  }
			break;
			case 4:
				size = 0;
				if ((fp = fopen("workWithExam.txt", "r")) == NULL){
				    	printf("Не удалось открыть файл");
				    	exit(1);
				}
				while (1){
					exam = (struct exam*)calloc(1, sizeof(struct exam));
					if(fscanf(fp,"%d",&number) == EOF){
						break;
					}
					exam -> amount = number;
					marks = (int*)calloc(ARRSIZE, sizeof(int));
					for(int i = 0; i < exam -> amount; i++){
						if(fscanf(fp,"%d",&number) == EOF){
							break;
						}
						*(marks + i) = number;
					}
					exam -> marks = marks;
				      	str = (char*)calloc(ARRSIZE, sizeof(char));
					if(fscanf(fp,"%s",str) == EOF){
						break;
					}
					exam -> examName = str;
					if(fscanf(fp,"%ld",&time) == EOF){
						break;
					}
					exam -> date = time;
					str = (char*)calloc(ARRSIZE, sizeof(char));
					if(fscanf(fp,"%s",str) == EOF){
						break;
					}
					exam -> professorName = str;
					*(exams + size) = *exam;
					size++;
				}
				fclose(fp);
			break;
			case 6:
				number = 0;
				while(number != 1 && number != 2){
					printf("введите 1, чтобы отсортировать по количеству оценок\n2 - по названию экзамена\n");
					scanf("%d", &number);
					switch(number){
						case 1:
							qsort(exams, size, sizeof(struct exam), cmpExamAmount);
							break;
						case 2:
							qsort(exams, size, sizeof(struct exam), cmpExamName);
							break;
					}
				}
			break;
			case 7:
				printf("введите номер строки для удаления\n");
				scanf("%d", &number);
				if(number < size && number > -1){
						free(exams[number].examName);
						free(exams[number].professorName);
						free(exams[number].marks);
					for(int i = number; i < size - 1; i++){
						*(exams + i) = *(exams + i + 1);
					}
					size--;
				}
			break;
			case 8:
				printf("введите номер строки для редактирования\n");
				scanf("%d", &number);
				if(number < size && number > -1){
						free(exams[number].examName);
						free(exams[number].professorName);
						free(exams[number].marks);
						size = workWithExamWE(number, exams, size);
				}
				else{
					printf("\n неверный индекс\n");
				}
			break;
		}  
	}
	for(int i = 0; i < size; i++){
		free(exams[i].examName);
		free(exams[i].professorName);
		free(exams[i].marks);					
	}
	free(exams);
}
