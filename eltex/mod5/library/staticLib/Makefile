result: f1.o f2.o libstatic.a
	cc main.c -L. -lstatic -o result
libstatic.a: f1.o f2.o
	ar rc libstatic.a f1.o f2.o
	ranlib libstatic.a
f1.o: f1.c
	cc -c f1.c
f2.o: f2.c
	cc -c f2.c
clean:
	rm f1.o f2.o libstatic.a result
