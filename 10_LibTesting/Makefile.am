SUBDIRS = src tests

demo:	all
	./src/buf

checklog:	check
	cat tests/*.log

gcov:	check
	$(MAKE) $(MAKEFLAGS) -C src gcov
