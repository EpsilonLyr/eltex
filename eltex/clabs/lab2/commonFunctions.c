#include <stdio.h>


void change(char *str){
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] == '\n'){
			str[i] = '\0';
			break;
		}
	}
}
