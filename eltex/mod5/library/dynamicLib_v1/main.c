#include <stdio.h>

extern int f1(int x, int y);
extern int f2(int x, int y);

int main(){
	int x = 2;
	int y = 3;
	printf("%d\n%d\n", f1(x,y), f2(x,y));
}
