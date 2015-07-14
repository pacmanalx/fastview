all:	main

main:	main.o
	gcc main.o -o fastview -lncurses
	./compile

main.o:	main.c
	gcc -c main.c

clean:
	rm *o fastview

