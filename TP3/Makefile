CC = gcc

CFLAGS = -Wall -ggdb -std=c99 -lglpk

DEPS = order.h orderSolver.h

OBJ = order.o main.o orderSolver.o

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY : clean

clean:
	-rm -f $(OBJ)
	-rm -f
