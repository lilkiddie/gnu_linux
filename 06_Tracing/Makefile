CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -ldl

BINARY = move
LIBRARY = libprotect.so
GENERATED = $(BINARY) $(LIBRARY)
TEMP_FILES = *.txt

.PHONY: all test test_protect clean

all: $(BINARY) $(LIBRARY)

$(BINARY): move.c
	$(CC) $(CFLAGS) $< -o $@

$(LIBRARY): libprotect.c
	$(CC) -shared -fPIC $< -o $@ $(LDFLAGS)

test: $(BINARY)
	@echo "=== Running basic tests ==="
	
	@echo "Test 1: Missing input file"
	@rm -f missing.txt out.txt
	@./move missing.txt out.txt 2>/dev/null; test "$$?" = "10"
	
	@echo "Test 2: Cannot create output (bad path)"
	@rm -f goodin.txt
	@echo "data" > goodin.txt
	@./move goodin.txt /root/cannot_write_here.txt 2>/dev/null; \
	EXIT=$$?; test $$EXIT = "11" && test -f goodin.txt
	
	@echo "Test 3: Normal operation"
	@rm -f src.txt dst.txt
	@echo "test content" > src.txt
	@./move src.txt dst.txt
	@test ! -f src.txt && test -f dst.txt
	@grep -q "test content" dst.txt
	
	@echo "Test 4: Same file"
	@rm -f same.txt
	@echo "data" > same.txt
	@./move same.txt same.txt 2>/dev/null; test "$$?" = "2" && test -f same.txt
	
	@echo "Test 5: Empty file"
	@rm -f empty1.txt empty2.txt
	@touch empty1.txt
	@./move empty1.txt empty2.txt
	@test ! -f empty1.txt && test -f empty2.txt && test ! -s empty2.txt
	
	@echo "=== All basic tests passed ==="

test_protect: $(BINARY) $(LIBRARY)
	@echo "=== Running protection tests ==="
	
	@echo "Test 1: File with PROTECT in name"
	@rm -f MY_PROTECT_FILE.txt result.txt
	@echo "secret" > MY_PROTECT_FILE.txt
	@LD_PRELOAD=./$(LIBRARY) ./move MY_PROTECT_FILE.txt result.txt 2>/dev/null; \
	test "$$?" = "15" && test -f MY_PROTECT_FILE.txt
	
	@echo "Test 2: Normal file with library"
	@rm -f normal.txt output.txt
	@echo "ok" > normal.txt
	@LD_PRELOAD=./$(LIBRARY) ./move normal.txt output.txt
	@test ! -f normal.txt && test -f output.txt
	
	@echo "=== All protection tests passed ==="

clean:
	rm -f $(GENERATED) $(TEMP_FILES)
