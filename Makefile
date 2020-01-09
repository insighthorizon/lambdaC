test:
	make build;
	make run;

build:
	gcc main.c -o main.o -c;
	gcc main.o -o lambdaC_test;

run:
	./lambdaC_test;

clean:
	-rm main.o;
