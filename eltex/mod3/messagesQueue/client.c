#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100
#define TYPE 1

void change(char *str){
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] == '\n'){
			str[i] = '\0';
			break;
		}
	}
}

int main(int argc, char *argv[]){
	char pathname[] = "client.c";
	key_t key;
	int id;
	if((key = ftok(pathname,0)) < 0){
		printf("Can\'t generate key\n");
		exit(-1);
	}
	if((id = msgget(key, 0666 | IPC_CREAT)) < 0){
		printf("Can\'t get msqid\n");
		exit(-1);
	} 
	struct mymsgbuf{
		long mtype;
		pid_t mpid;
		char mtext[SIZE];
	} buf;
	pid_t pid = getpid();
	char str[100];
	printf("вводите сообщения для сервера\n");
	for(int i = 0; i < 5; i++){
		buf.mtype = TYPE;
		buf.mpid = pid;
		fgets(str, SIZE, stdin);
		change(str);
		strcpy(buf.mtext, str);
		msgsnd(id, (struct msgbuf *)&buf,SIZE,0);
		msgrcv(id, (struct msgbuf *)&buf,SIZE,pid,0);
		printf("%s\n", buf.mtext);
	}
	return 0;
}
