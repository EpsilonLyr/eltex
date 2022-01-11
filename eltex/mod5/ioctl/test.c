#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
 
#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

 
int main(){
	int fd;
	int32_t value, number;

	fd = open("/dev/mydev", O_RDWR);
	if(fd < 0) {
		printf("Cannot open device file\n");
		return 0;
	}

	printf("write value to /dev/mydev\n");
	scanf("%d",&number);
	ioctl(fd, WR_VALUE, (int32_t*) &number); 
	ioctl(fd, RD_VALUE, (int32_t*) &value);
	printf("Value from /dev/mydev is %d\n", value);
	close(fd);
        
}
