CC = gcc
CFLAGS = -Wall -g

BINARIES = maze size_from_command_line symbols_from_command_line rng_seed

all: $(BINARIES)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

maze: maze.o
	$(CC) $(CFLAGS) -o $@ $<

size_from_command_line: maze.c
	cp maze.c size_from_command_line.c
	patch -u size_from_command_line.c < patch1.patch
	$(CC) $(CFLAGS) -o $@ size_from_command_line.c

symbols_from_command_line: size_from_command_line.c
	cp size_from_command_line.c symbols_from_command_line.c
	patch -u symbols_from_command_line.c < patch2.patch
	$(CC) $(CFLAGS) -o $@ symbols_from_command_line.c

rng_seed: symbols_from_command_line.c
	cp symbols_from_command_line.c rng_seed.c
	patch -u rng_seed.c < patch3.patch
	$(CC) $(CFLAGS) -o $@ rng_seed.c

run: all
	./maze
	./size_from_command_line 6
	./symbols_from_command_line ".#" 6
	./rng_seed 123 ".#" 6

clean:
	rm -f $(BINARIES) *.o *from_command_line.c rng_seed.c