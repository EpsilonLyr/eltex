#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARRSIZE 100
#define WFLAG -1
/*
void change(char *str){
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] == '\n'){
			str[i] = '\0';
			break;
		}
	}
}

struct page{
	int pageNum;
	int stringNum;
	char *text;
	char *date;
};

int workWithPageWE(int edit, struct page *pages, int size){
	struct page *page;
	int number = 0;
	char *str;
	page = (struct page*)calloc(1, sizeof(struct page));
	printf("введите  pageNum\n");
	scanf("%d", &number);
	page -> pageNum = number;
	printf("%d\n", page -> pageNum);
	printf("введите  stringNum\n");
	scanf("%d", &number);
	page -> stringNum = number;
	printf("%d\n", page -> stringNum);
	printf("введите  text\n");
	str = (char*)calloc(ARRSIZE, sizeof(char));
	fgets(str, ARRSIZE, stdin);
	fgets(str, ARRSIZE, stdin);
	change(str);
	page -> text = str;
	printf("%s\n", page -> text);
	printf("введите  date\n");
	str = (char*)calloc(ARRSIZE, sizeof(char));
	fgets(str, ARRSIZE, stdin);
	change(str);
	page -> date = str;
	printf("%s\n", page -> date);
	if(edit == WFLAG){
		*(pages + size) = *page;
		size++;
	}
	else{
		*(pages + edit) = *page;
	}
	return size;
}

int cmpPageNum(const void *x1, const void *x2){
	return ((*(struct page *)x1).pageNum - (*(struct page *)x2).pageNum);
}

int cmpPageStringNum(const void *x1, const void *x2){
	return ((*(struct page *)x1).stringNum - (*(struct page *)x2).stringNum);
}


void workWithPage(){
	int sum = 0;
	int choice = 0;
	int number = 0;
	char *str;
	FILE *fp;
	struct page pages[ARRSIZE];
	struct page *page;
	int size = 0;
	while(choice != 1){
		printf("введите 1, чтобы завершить работу с таблицей\n2 - чтобы ввести данные\n");
		printf("3 - чтобы сохранить данные в таблицу\n4 - чтобы загрузить таблицу\n5 - чтобы просмотреть таблицу\n");
		printf("6 - сортировка\n7 - удаление\n8 - редактирование\n9 - сумма всех номеров страниц\n");
		scanf("%d", &choice);
		switch(choice){
			case 2:
				size = workWithPageWE(WFLAG, pages, size);
			break;
			case 3:
				  if ((fp = fopen("workWithPage.txt", "w")) == NULL){
				    	printf("Не удалось открыть файл");
				    	exit(1);
				  }
				  for(int i = 0; i < size; i++){
				  	printf("%d _-_ %d\n",pages[i].pageNum, pages[i].stringNum);
				  	fprintf(fp, "%d\n", pages[i].pageNum);
				  	fprintf(fp, "%d\n", pages[i].stringNum);
				  	fprintf(fp, "%s\n", pages[i].text);
				  	fprintf(fp, "%s\n", pages[i].date);
				  }
				  fclose(fp);
			break;
			case 5:
				for(int i = 0; i < size; i++){
				  	printf("%d ;", pages[i].pageNum);
				  	printf("%d ;", pages[i].stringNum);
				  	printf("%s ;", pages[i].text);
				  	printf("%s ;", pages[i].date);
				  	printf("\n");
				  }
			break;
			case 4:
				size = 0;
				if ((fp = fopen("workWithPage.txt", "r")) == NULL){
				    	printf("Не удалось открыть файл");
				    	exit(1);
				}
				while (1){
					page = (struct page*)calloc(1, sizeof(struct page));
					if(fscanf(fp,"%d",&number) == EOF){
						break;
					}
					page -> pageNum = number;
				      	if(fscanf(fp,"%d",&number) == EOF){
						break;
					}
					page -> stringNum = number;
					str = (char*)calloc(ARRSIZE, sizeof(char));
					if(fscanf(fp,"%s",str) == EOF){
						break;
					}
					page -> text = str;
					str = (char*)calloc(ARRSIZE, sizeof(char));
					if(fscanf(fp,"%s",str) == EOF){
						break;
					}
					page -> date = str;
					*(pages + size) = *page;
					size++;
				}
				fclose(fp);
			break;
			case 6:
				number = 0;
				while(number != 1 && number != 2){
					printf("введите 1, чтобы отсортировать по номеру\n2 - по количеству строк\n");
					scanf("%d", &number);
					switch(number){
						case 1:
							qsort(pages, size, sizeof(struct page), cmpPageNum);
							break;
						case 2:
							qsort(pages, size, sizeof(struct page), cmpPageStringNum);
							break;
					}
				}
			break;
			case 7:
				printf("введите номер строки для удаления\n");
				scanf("%d", &number);
				if(number < size && number > -1){
						free(pages[number].text);
						free(pages[number].date);
						*page = *(pages + number);
						free(page);
					for(int i = number; i < size - 1; i++){
						*(pages + i) = *(pages + i + 1);
					}
					size--;
				}
			break;
			case 8:
				printf("введите номер строки для редактирования\n");
				scanf("%d", &number);
				if(number < size && number > -1){
						free(pages[number].text);
						free(pages[number].date);
						*page = *(pages + number);
						free(page);
						size = workWithPageWE(number, pages, size);
				}
				else{
					printf("\n неверный индекс\n");
				}
			break;
			case 9:
				for(int i = 0; i < size; i++){
				  	sum += pages[i].pageNum;
				  }
				  printf("\nсумма всех номеров страниц = %d\n", sum);
			break;
			
		}  
		
	}
	
	for(int i = 0; i < size; i++){
		free(pages[i].text);
		free(pages[i].date);
		*page = *(pages + i);
		free(page);
	}
}

struct exam{
	char *examName;
	char *examDate;
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
	printf("введите  examDate\n");
	str = (char*)calloc(ARRSIZE, sizeof(char));
	fgets(str, ARRSIZE, stdin);
	change(str);
	exam -> examDate = str;
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

void workWithExam(){
	int choice = 0;
	int number = 0;
	int *marks;
	char *str;
	FILE *fp;
	int size = 0;
	struct exam exams[ARRSIZE];
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
				  	fprintf(fp, "%s\n", exams[i].examDate);
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
				  	printf("%s ;", exams[i].examDate);
				  	printf("%s ;", exams[i].professorName);
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
					str = (char*)calloc(ARRSIZE, sizeof(char));
					if(fscanf(fp,"%s",str) == EOF){
						break;
					}
					exam -> examDate = str;
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
						free(exams[number].examDate);
						free(exams[number].professorName);
						free(exams[number].marks);
						*exam = *(exams + number);
						free(exam);
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
						free(exams[number].examDate);
						free(exams[number].professorName);
						free(exams[number].marks);
						*exam = *(exams + number);
						free(exam);
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
		free(exams[i].examDate);
		free(exams[i].professorName);
		free(exams[i].marks);
		*exam = *(exams + i);
		free(exam);					
	}
}


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

void workWithLearner(){
	int choice = 0;
	int number = 0;
	char *str;
	FILE *fp;
	struct learner learners[ARRSIZE];
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
						*learner = *(learners + number);
						free(learner);
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
						*learner = *(learners + number);
						free(learner);
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
		*learner = *(learners + i);
		free(learner);
	}
}
*/


int main(void) {
	int numOfTable = 0;
	while(numOfTable < 1 || numOfTable > 4){
		printf("введите\n1, чтобы работать с таблицей page\n2, чтобы работать с таблицей exam\n");
		printf("3, чтобы работать с таблицей learner\n4, чтобы выйти\n");
		scanf("%d", &numOfTable);
		switch (numOfTable) {
        		case 1:
        			execl("2labPage", "2labPage", NULL);
        			perror("EXEC:");
            			//workWithPage();
            			break;
        		case 2:
        			execl("2labExam", "2labExam", NULL);
        			perror("EXEC:");
           			//workWithExam();
            			break;
        		case 3:
        			execl("2labLearner", "2labLearner", NULL);
        			perror("EXEC:");
            			//workWithLearner();
            			break;
        		case 4:
        			exit(0);
    		}
	}
}
