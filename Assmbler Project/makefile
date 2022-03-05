assembler: assembler.o func.o fileCheck.o filesMake.o
	gcc -g -Wall -ansi -pedantic assembler.o func.o fileCheck.o filesMake.o -lm -o assembler
assembler.o: assembler.c assembler.h 
	gcc -g -c -Wall -ansi -pedantic assembler.c -o assembler.o
func.o: func.c assembler.h func.h
	gcc -g -c -Wall -ansi -pedantic func.c -o func.o
fileCheck.o: fileCheck.c assembler.h
	gcc -g -c -Wall -ansi -pedantic fileCheck.c -o fileCheck.o
filesMake.o: filesMake.c assembler.h
	gcc -g -c -Wall -ansi -pedantic filesMake.c -o filesMake.o 
