#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define P 133
#define A 5
#define X 3



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

int nod(int n1, int n2)
{
 	int div;
  	if (n1 == n2){
    		return n1;
    	}
  	int d = n1 - n2; 
  	if (d < 0){
    		d = -d; 
    		div = nod(n1, d);
  	}
  	else{
    		div = nod(n2, d); 
 	}
	return div;
}


int expression(int a, int k, int i){
	return ((X * a) + (k * i)) % (P - 1);
}


int main(void) {
	FILE *fp;
	unsigned long long int openKey = ((unsigned long long int)pow_mod(A, X, P));
	printf("%llu\n",openKey); 
	char c = 'a';
	int code = (int)c;
	printf("code = %d\n",code); 
	unsigned long long int a = 0;
	unsigned long long int b = 0;
	int uid = 0;
	srand ( time(NULL) );
	int k = (rand() % (P - 3)) + 2;
	int nd = nod(k, P - 1);
	while(nd != 1){
		k = (rand() % (P - 3)) + 2;
		nd = nod(k, P - 1);
	}
	unsigned long long int r = 1;
	printf("k = %d\n", k);
	a = ((unsigned long long int)pow_mod(A, k, P));
	printf("a = %llu\n", a);

	int answ = 0;
	unsigned long long int i = -1;
	while(answ != code){
		i++;
		answ = expression(a, k, i);
	}
	b = i;
	printf("b = %llu\n", b);
	
	if ((fp = fopen("cr.txt", "w")) == NULL){
		printf("Не удалось открыть файл");
		exit(1);
	}
	fprintf(fp, "%llu\n%d\n%llu\n%llu\n", openKey, code, a, b);
	fclose(fp);
	fp = NULL;
	
}
