#Jeux des petis chevaux

CC = gcc
FLAGS = -ansi -Wall
OBJS = exe/main.o exe/petits_chevaux.o exe/pile_LIFO.o
EXE = exe/code

$ (EXE) : $(OBJS)
	$(CC)  $(FLAGS) $(OBJS) -o $(EXE)

exe/main.o : src/main.c
	$(CC) $(FLAGS) -c src/main.c -o exe/main.o

exe/petits_chevaux.o : src/lib/petits_chevaux.c
	$(CC) $(FLAGS) -c src/lib/petits_chevaux.c -o exe/petits_chevaux.o

exe/pile_LIFO.o : src/lib/pile_LIFO.c
	$(CC) $(FLAGS) -c src/lib/pile_LIFO.c -o exe/pile_LIFO.o

clean :
	rm exe/code
	rm exe/*.o
