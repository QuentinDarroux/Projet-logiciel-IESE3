#Jeux des petis chevaux

CC = gcc
FLAGS = -ansi -Wall
OBJS = main.o
EXE = code

$ (EXE) : $(OBJS)
	$(CC)  $(FLAGS) $(OBJS) -o $(EXE)

main.o : src/main.c
	$(CC) $(FLAGS) -c src/main.c -o main.o
