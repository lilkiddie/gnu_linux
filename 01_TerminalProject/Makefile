SRC=Show.c
EXE=Show
CC=gcc
CFLAGS=-Wall
LIBS=-lncurses

%:	%.c
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

clean:
	rm -f o oo *.o $(EXE)
