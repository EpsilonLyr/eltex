result: libdynamic.so
	cc main.c -o result -ldl
libdynamic.so: f1.o f2.o
	cc -shared -o libdynamic.so f1.o f2.o
f1.o: f1.c
	cc -fPIC -c f1.c
f2.o: f2.c
	cc -fPIC -c f2.c
clean:
	rm f1.o f2.o libdynamic.so result
