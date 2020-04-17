#Jeux des petis chevaux

CC = gcc
FLAGS = -ansi -Wall
OBJS = exe/main.o
EXE = exe/code

$ (EXE) : $(OBJS)
	$(CC)  $(FLAGS) $(OBJS) -o $(EXE)

exe/main.o : src/main.c
	$(CC) $(FLAGS) -c src/main.c -o exe/main.o
