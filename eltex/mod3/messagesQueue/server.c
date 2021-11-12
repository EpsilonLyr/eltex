#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100
#define TYPE 1

int main(){
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
	while(1){
		if(msgrcv(id,&buf,SIZE,TYPE,0)<0){
			printf("Can\'t receive message from queue\n");
			exit(-1);
		}
		buf.mtype = buf.mpid;
		printf("%s\n", buf.mtext);
		strcpy(buf.mtext, "received");
		msgsnd(id, (struct msgbuf *)&buf,SIZE,0);
	}
	return 0;
}
