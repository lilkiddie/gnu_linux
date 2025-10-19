.PHONY: clean disclean
TRASH = *.o *.out
GENS = prog prog-static prog-dynamic libout.a libout.so
CFLAGS = -Wall -fPIC

all: prog prog-static prog-dynamic README

fun.o prog.o:	outlib.h

libout.so:		fun.o const.o
		$(CC) $^ -o $@ -shared

libout.a:		libout.a(fun.o const.o)

prog:	prog.o fun.o const.o

prog-static:	prog.o libout.a
		$(CC) $< libout.a -o $@

prog-dynamic: prog.o libout.so
		$(CC) $< -L. -lout -o $@

README: prog
		LD_LIBRARY_PATH='pwd' ./$< > $@ 2>&1

test : all
		./prog > prog_no_params.out 2>&1
		./prog-static > prog-static_no_params.out 2>&1
		LD_LIBRARY_PATH=`pwd` ./prog-dynamic > prog-dynamic_no_params.out 2>&1
		cmp prog_no_params.out prog-static_no_params.out
		cmp prog-static_no_params.out prog-dynamic_no_params.out

		./prog testparam > prog_one_param.out 2>&1
		./prog-static testparam > prog-static_one_param.out 2>&1
		LD_LIBRARY_PATH=`pwd` ./prog-dynamic testparam > prog-dynamic_one_param.out 2>&1
		cmp prog_one_param.out prog-static_one_param.out
		cmp prog-static_one_param.out prog-dynamic_one_param.out

		./prog param1 param2 param3 > prog_three_params.out 2>&1
		./prog-static param1 param2 param3 > prog-static_three_params.out 2>&1
		LD_LIBRARY_PATH=`pwd` ./prog-dynamic param1 param2 param3 > prog-dynamic_three_params.out 2>&1
		cmp prog_three_params.out prog-static_three_params.out
		cmp prog-static_three_params.out prog-dynamic_three_params.out

clean:
		rm -f $(TRASH)

disclean:	clean
		rm -f $(GENS)
