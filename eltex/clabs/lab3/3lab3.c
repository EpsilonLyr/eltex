#include <stdio.h>
#include <stdlib.h>
#define ARRSIZE 100

int cut(char *str, char **strings) {
    	char *cut;
    	int len = 0;
    	int depth = 0;
    	int maxDepth = 0;
    	int begin = 0;
    	int end = 0;
    	int j = 0;
    	int count = 0;
    	int open = 0;
    	int close = 0;
    	do{
    	    	cut = (char*)calloc(ARRSIZE, sizeof(char));
	    	depth = 0;
	   	maxDepth = 0;
	    	begin = 0;
	    	end = 0;
	    	j = 0;
	    	for(int i = 0; str[i] != '\0'; i++){
	    		if(*(str + i) == ')'){
	    			if(depth == maxDepth){
	    				end = i;
	    			}
	    			depth--;
	    		}
	    		if(*(str + i) == '('){
	    			depth++;
	    			if(depth > maxDepth){
	    				begin = i;
	    				maxDepth = depth;
	    			}
	    		}
	    	}
	    	if(depth != 0){
	    		printf("неправильная скобочная последовательность\n");
	    		free(cut);
	    		cut = NULL;
	    		exit(1);
	    	}
	    	for(int i = begin + 1; i < end; i++, j++){
	    		*(cut + j) = *(str + i);
	    	}
	    	*(cut + j) = '\0';
	    	if(end - begin != 0){
	    		for(int j = 0; j <= end - begin; j++) {
	    			for(int i = begin; str[i] != '\0'; i++){
	    				*(str + i) = *(str + i + 1);
	    			}
	    		}
	    	}
	    	printf("\ncut=%s\n", cut);
	    	printf("\nstr=%s\n", str);
	    	*(strings + count) = cut;
	    	count++;
    	}while(maxDepth != 0);
    	for(int i = 0; str[i] != '\0'; i++){
		len++;
    	}
    	if(len == 0){
    		count--;
    	}
    	else{
    		strings[count - 1] = str;
   	}
    	return count;
}


int main(void) {
    	char *strings[ARRSIZE];
	char str[ARRSIZE] = "gf(fd(fdd)rt)t";
	int len = 0;
	int count = cut(str, strings);
	printf("\n%d\n", count);
    	for(int i = 0; i < count; i++){
    		printf("\n string = %s\n", *(strings + i));
    	}
    	for(int i = 0; str[i] != '\0'; i++){
		len++;
    	}
    	if(len != 0){
    		count--;
    	}
    	for(int i = 0; i < count; i++){
    		free(*(strings + i));
    		*(strings + i) = NULL;
    	}
}
