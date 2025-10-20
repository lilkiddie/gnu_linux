CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
SHELL = /bin/bash

.PHONY: all clean test

all: esub

esub: esub.c
	$(CC) $(CFLAGS) -o esub esub.c

clean:
	rm -f esub *.o

test: esub
	@echo "Test 1: Simple replacement"
	@bash -c 'diff <(./esub "world" "universe" "hello world") <(echo "hello world" | sed -E "s/world/universe/")'
	
	@echo "Test 2: Group reference"
	@bash -c 'diff <(./esub "([0-9]+)" "number:\\1" "test123") <(echo "test123" | sed -E "s/([0-9]+)/number:\\1/")'
	
	@echo "Test 3: Multiple groups"
	@bash -c 'diff <(./esub "([a-z]+) ([0-9]+)" "\\2-\\1" "abc 123") <(echo "abc 123" | sed -E "s/([a-z]+) ([0-9]+)/\\2-\\1/")'
	
	@echo "Test 4: No match"
	@bash -c 'diff <(./esub "xyz" "abc" "hello world") <(echo "hello world" | sed -E "s/xyz/abc/")'
	
	@echo "All tests passed!"
