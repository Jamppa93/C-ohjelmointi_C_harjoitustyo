HT: main.o  functions.o
	gcc main.o  functions.o -o HT -std=c99 -Wall -pedantic
main.o: main.c header.h
	gcc main.c -c -std=c99 -Wall -pedantic
functions.o: functions.c header.h
	gcc functions.c -c -std=c99 -Wall -pedantic


