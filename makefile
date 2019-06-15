solve: main.o maze.o
	gcc -o solve main.o maze.o

main.o: main.c maze.c maze.h
	gcc -c main.c

maze.o: maze.c maze.h
	gcc -c maze.c

clean: 
	/bin/rm -f *.o solve
