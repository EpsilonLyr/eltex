#include <stdio.h>
#include <stdlib.h>
#define ARRSIZE 100
#define P 133
#define A 5


unsigned long long int my_pow_mod(int a, int a1, int b, int b1, int c){
	unsigned long long int r = 1;
	for(int i = 0; i < b; i++){
		r *= a;
		r %= c;
	}
	for(int i = 0; i < b1; i++){
		r *= a1;
		r %= c;
	}
	return r;
}

unsigned  long  long  int sum_mod ( unsigned  long  long  int x, unsigned  long  long  int y, unsigned  long  long  int m) {
  	if (m - x > y){
    		return  x + y;
    	}
  	return  y - (m - x); 
}

// ( x * y ) mod m , 0 < x < m , y < m
// ( 5 * y ) mod m = ( y mod m ) + ( ( ( y * 2 ) mod m ) * 2 ) mod m
unsigned  long  long  int mul_mod (unsigned  long  long  int x, unsigned  long  long  int y, unsigned  long  long  int m) {
  	if(x > y) {
    		unsigned  long  long  int tmp = x;
    		x = y;
    		y = tmp; 
    	}
  	unsigned  long  long  int res = 0;
  	unsigned  long  long  int iy  = y;
  	while (x) {
    		if (x & 1){
      			res = sum_mod(res, iy, m);
      		}
    		iy  = sum_mod(iy, iy ,m);
    		x >>= 1;
    	}
  	return  res ; 
}

// ( x ^ n ) mod m , x < m , n > 0 , m > 0
// ( x ^ 5 ) mod m == ( ( x mod m ) * ( ( ( ( ( x ^ 2 ) mod m ) ) ^ 2 ) mod m ) ) mod m
unsigned  long  long  int pow_mod ( unsigned  long  long  int x, unsigned  long  long  int n, unsigned  long  long  int m) {
	unsigned  long  long  int res = 1;
  	while (n) {
    		if (n & 1){
    			res = mul_mod (res, x, m);
    		}
    		x = mul_mod ( x, x, m);
    		n >>= 1; 
    	}
	return res; 
}

int main(void) {
	FILE *fp;
	int openKey = 0;
	int m = 0;
	int a = 0;
	int b = 0;
	if ((fp = fopen("cr.txt", "r")) == NULL){
		printf("Не удалось открыть файл");
		exit(1);
	}
	fscanf(fp,"%d",&openKey);
	fscanf(fp,"%d",&m);
	fscanf(fp,"%d",&a);
	fscanf(fp,"%d",&b);
	printf("m = %d a = %d b = %d\n", m, a, b);
	unsigned long long int c1 = my_pow_mod(openKey, a, a, b, P);
	//unsigned long long int c1 = (openKey * (unsigned long long int)pow_mod(a, b, P));
	unsigned long long int c2 = ((unsigned long long int)pow_mod(A, m, P));
	printf("c1 = %llu c2 = %llu\n", c1, c2);
	if(c1 == c2){
		printf("подпись верна\n");
	}
	fclose(fp);
	fp = NULL;
	
	
}
