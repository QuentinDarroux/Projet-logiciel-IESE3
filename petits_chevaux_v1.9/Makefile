#Jeux des petis chevaux

CC = gcc
FLAGS = -ansi -Wall
OBJS = exe/main.o exe/fct_petits_chevaux.o
EXE = exe/code

$ (EXE) : $(OBJS)
	$(CC)  $(FLAGS) $(OBJS) -o $(EXE)

exe/main.o : src/main.c
	$(CC) $(FLAGS) -c src/main.c -o exe/main.o

exe/fct_petits_chevaux.o : src/lib/fct_petits_chevaux.c
	$(CC) $(FLAGS) -c src/lib/fct_petits_chevaux.c -o exe/fct_petits_chevaux.o
