C = gcc
FLAGS = -Wall

SRC = dateiarbeit.c generator.c loeser.c main.c sudoku.c
LIB = ./lib/cgi-lib.c ./lib/list-lib.c

compile:
	$(C) $(FLAGS) -o sudoku.cgi $(SRC) $(LIB)

clean:
	rm sudoku.cgi
