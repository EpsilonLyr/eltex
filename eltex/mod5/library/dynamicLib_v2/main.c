#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	void *ext_library;
	int x = 2; 
	int y = 3;
	int (*f)(int x, int y);
	if(argc != 2){
		printf("write funcion name(f1 or f2) as parametr\n");
		exit(-1);
	}
	ext_library = dlopen("./libdynamic.so", RTLD_LAZY);
	if (!ext_library){
		fprintf(stderr,"dlopen() error: %s\n", dlerror());
		return 1;
	};
	printf("___\n");
	f = dlsym(ext_library, argv[1]);
	//выводим результат работы процедуры
	printf("%s(%d, %d) = %d\n",argv[1], x, y,(*f)(x, y));

	//закрываем библиотеку
	dlclose(ext_library);
};


