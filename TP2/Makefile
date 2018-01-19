CC = gcc

CFLAGS = -Wall -ggdb -std=c99 -lssl -lcrypto

DEPS = Glouton.h

OBJ = Glouton.o main.o

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY : clean

clean:
	-rm -f $(OBJ)
	-rm -f 
