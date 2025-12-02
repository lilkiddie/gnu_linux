bin_PROGRAMS = hasher
hasher_SOURCES = hasher.c
hasher_CFLAGS = -Wall -Wextra $(RHASH_CFLAGS)
hasher_LDADD = $(RHASH_LIBS)

if USE_READLINE
hasher_CFLAGS += $(READLINE_CFLAGS)
hasher_LDADD += $(READLINE_LIBS)
endif

check-local: hasher
	@echo "Running MD5 uppercase (hex) test..."
	@echo 'MD5 "hello' | ./hasher > test_md5_upper.out
	@echo -n "hello" | md5sum | awk '{print toupper($$1)}' > test_md5_upper.exp
	@cmp test_md5_upper.out test_md5_upper.exp && echo "  MD5 uppercase test: PASSED" || (echo "  MD5 uppercase test: FAILED" && cat test_md5_upper.out && cat test_md5_upper.exp && exit 1)
	
	@echo "Running SHA1 uppercase (hex) test..."
	@echo 'SHA1 "world' | ./hasher > test_sha1_upper.out
	@echo -n "world" | sha1sum | awk '{print toupper($$1)}' > test_sha1_upper.exp
	@cmp test_sha1_upper.out test_sha1_upper.exp && echo "  SHA1 uppercase test: PASSED" || (echo "  SHA1 uppercase test: FAILED" && exit 1)
	
	@echo "Running md5 lowercase (base64) test..."
	@echo 'md5 "test' | ./hasher > test_md5_lower.out
	@test -s test_md5_lower.out && echo "  md5 lowercase test: PASSED" || (echo "  md5 lowercase test: FAILED" && exit 1)
	
	@echo "Running sha1 lowercase (base64) test..."
	@echo 'sha1 "data' | ./hasher > test_sha1_lower.out
	@test -s test_sha1_lower.out && echo "  sha1 lowercase test: PASSED" || (echo "  sha1 lowercase test: FAILED" && exit 1)
	
	@echo "Running TTH test..."
	@echo 'TTH "example' | ./hasher > test_tth.out
	@test -s test_tth.out && echo "  TTH test: PASSED" || (echo "  TTH test: FAILED" && exit 1)
	
	@rm -f test_*.out test_*.exp
	@echo ""
	@echo "All tests passed!"

clean-local:
	rm -f test_*.out test_*.exp

distclean-local:
	rm -f Makefile.in aclocal.m4 configure config.h.in config.h.in~
	rm -rf autom4te.cache
	rm -f compile depcomp install-sh missing test-driver
	rm -f config.log config.status stamp-h1
	rm -f *~

.PHONY: gitclean
gitclean:
	git clean -xdf
