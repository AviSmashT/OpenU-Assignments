mycomp: mycomp.o complex.o analysis.o
	gcc -g -Wall -ansi -pedantic mycomp.o complex.o analysis.o -lm -o mycomp
mycomp.o: mycomp.c complex.h
	gcc -g -c -Wall -ansi -pedantic mycomp.c -o mycomp.o 
complex.o: complex.c complex.h
	gcc -g -c -Wall -ansi -pedantic complex.c -o complex.o 
analysis.o: analysis.c complex.h
	gcc -g -c -Wall -ansi -pedantic analysis.c -o analysis.o 	
