#include "2lab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct page{
	int pageNum;
	int stringNum;
	char *text;
	time_t date;
};

int workWithPageWriteEdit(int edit, struct page *pages, int size){
	int d = 0;
	int m = 0;
	int y = 0; 
	int h = 0;
	int min = 0;
	printf("%d __ Вводите дату в формате dd.MM.yyyy hh:mm\n", y);
  	if(scanf("%d.%d.%d %d:%d", &d, &m, &y, &h, &min) == 5){
  		struct page *page = (struct page*)calloc(1, sizeof(struct page));
  		struct tm *time = (struct tm*)calloc(1, sizeof(struct tm));
		printf("Принято\n");
		time->tm_year = y-1900;
		time->tm_mon = m-1;
		time->tm_mday = d;
		time->tm_min = min;
		time->tm_hour = h;
		char *f = asctime(time);
		puts(f);
		page -> date = mktime(time);
		free(time);
		int number = 0;
		char *str;
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
		if(edit == WFLAG){
			*(pages + size) = *page;
			size++;
		}
		else{
			*(pages + edit) = *page;
		}
	}
	else{
    		printf("неверный формат\n");
    		exit(-1);
    	}
	return size;
}

int cmpPageNum(const void *x1, const void *x2){
	return ((*(struct page *)x1).pageNum - (*(struct page *)x2).pageNum);
}

int cmpPageDate(const void *x1, const void *x2){
	return ((*(struct page *)x1).date - (*(struct page *)x2).date);
}

int cmpPageStringNum(const void *x1, const void *x2){
	return ((*(struct page *)x1).stringNum - (*(struct page *)x2).stringNum);
}


int main(void) {
	int sum = 0;
	int choice = 0;
	int number = 0;
	time_t time = 0;
	char *str;
	FILE *fp;
	struct page *pages = (struct page*)calloc(ARRSIZE, sizeof(struct page));
	struct page *page;
	int size = 0;
	while(choice != 1){
		printf("введите 1, чтобы завершить работу с таблицей\n2 - чтобы ввести данные\n");
		printf("3 - чтобы сохранить данные в таблицу\n4 - чтобы загрузить таблицу\n5 - чтобы просмотреть таблицу\n");
		printf("6 - сортировка\n7 - удаление\n8 - редактирование\n9 - сумма всех номеров страниц\n");
		scanf("%d", &choice);
		switch(choice){
			case 2:
				size = workWithPageWriteEdit(WFLAG, pages, size);
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
				  	fprintf(fp, "%ld\n", pages[i].date);
				  }
				  fclose(fp);
			break;
			case 5:
				for(int i = 0; i < size; i++){
				  	printf("%d ;", pages[i].pageNum);
				  	printf("%d ;", pages[i].stringNum);
				  	printf("%s ;", pages[i].text);
				  	printf("%s", ctime(&(pages[i].date)));
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
				      	if(fscanf(fp,"%ld",&time) == EOF){
						break;
					}
					page -> date = time;
					*(pages + size) = *page;
					size++;
				}
				fclose(fp);
			break;
			case 6:
				number = 0;
				while(number > 3 || number < 1){
					printf("введите 1, чтобы отсортировать по номеру\n2 - по количеству строк\n3 - по дате\n");
					scanf("%d", &number);
					switch(number){
						case 1:
							qsort(pages, size, sizeof(struct page), cmpPageNum);
							break;
						case 2:
							qsort(pages, size, sizeof(struct page), cmpPageStringNum);
							break;
						case 3:
							qsort(pages, size, sizeof(struct page), cmpPageDate);
							break;
					}
				}
			break;
			case 7:
				printf("введите номер строки для удаления\n");
				scanf("%d", &number);
				if(number < size && number > -1){
						free(pages[number].text);
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
						size = workWithPageWriteEdit(number, pages, size);
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
	}
	free(pages);
}
