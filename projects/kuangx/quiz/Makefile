CFLAGS= -Wall -fpic -coverage -lm -std=c99

all: testme
	./testme
	gcov -b -u testme.c

testme: testme.c
	gcc $(CFLAGS) -o testme testme.c

clean:
	rm -rf testme *.gcda *gcno *gcov
