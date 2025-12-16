all: range

range: range.c
	gcc -O0 -g -o range range.c

generate-expected: range
	gdb --batch --quiet -x script1.gdb 2>&1 | grep "^@@@" > expected1.txt || true
	gdb --batch --quiet -x script2.gdb 2>&1 | grep "^@@@" > expected2.txt || true

test: range
	gdb --batch --quiet -x script1.gdb 2>&1 | grep "^@@@" > output1.txt || true
	diff output1.txt expected1.txt
	gdb --batch --quiet -x script2.gdb 2>&1 | grep "^@@@" > output2.txt || true
	diff output2.txt expected2.txt

clean:
	rm -f range output1.txt output2.txt

.PHONY: all test clean generate-expected
