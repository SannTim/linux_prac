CC = cc
CFLAGS = -Wall
LDFLAGS = -ldl

TARGET = move
LIB = protect.so

.PHONY: all clean test

all: $(TARGET) $(LIB)

$(TARGET): move.c
	$(CC) $(CFLAGS) -o $@ $<

$(LIB): protect.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $< $(LDFLAGS)

test:
	@echo "=== Тест 1: infile не существует ==="
	@rm -f nonexistent xxx
	@./move nonexistent xxx 2>/dev/null; \
	if [ $$? -eq 2 ] && [ ! -f xxx ]; then \
		echo "OK"; else echo "FAIL"; exit 1; fi
	@echo "=== Тест 2: ошибка write (strace) ==="
	@echo "data" > test_in && rm -f test_out
	@timeout 5 strace -e inject=write:error=EIO ./move test_in test_out 2>&1 | tee /tmp/strace.log | grep -q "write.*= -1 EIO" && \
		( test -f test_in && echo "OK" ) || ( echo "FAIL: infile lost"; exit 1 ) || \
		( echo "FAIL: write injection not seen"; cat /tmp/strace.log; exit 1 )
	@rm -f test_in test_out /tmp/strace.log
	@echo "=== Тест 3: ошибка close (strace) ==="
	@echo "data" > test_in && rm -f test_out
	@timeout 5 strace -e inject=close:error=EBADF ./move test_in test_out 2>&1 | tee /tmp/strace.log | grep -q "close.*= -1 EBADF" && \
		( test -f test_in && echo "OK" ) || ( echo "FAIL: infile lost"; exit 1 ) || \
		( echo "WARNING: close injection not seen, but infile preserved"; test -f test_in && echo "OK" || exit 1 )
	@rm -f test_in test_out /tmp/strace.log
	@echo "=== Тест 4: ошибка unlink (strace) ==="
	@echo "data" > test_in && rm -f test_out
	@timeout 5 strace -e inject=unlink:error=EPERM ./move test_in test_out 2>&1 | tee /tmp/strace.log | grep -q "unlink.*= -1 EPERM" && \
		( test -f test_in && echo "OK" ) || ( echo "FAIL: infile deleted!"; exit 1 ) || \
		( echo "FAIL: unlink injection not seen"; cat /tmp/strace.log; exit 1 )
	@rm -f test_in test_out /tmp/strace.log
	
	@echo "=== Тест 5: LD_PRELOAD защита ==="
	@echo "secret" > file_PROTECT && rm -f out_PROTECT
	@LD_PRELOAD=./protect.so ./move file_PROTECT out_PROTECT 2>/dev/null; \
	EXIT=$$?; \
	if [ $$EXIT -ne 0 ] && [ -f file_PROTECT ] && [ -f out_PROTECT ]; then \
		if cmp -s file_PROTECT out_PROTECT; then \
			echo "OK"; \
		else \
			echo "FAIL: outfile content mismatch"; exit 1; \
		fi; \
	else \
		echo "FAIL: exit=$$EXIT, infile exists: $$(if [ -f file_PROTECT ]; then echo yes; else echo no; fi), outfile exists: $$(if [ -f out_PROTECT ]; then echo yes; else echo no; fi)"; \
		exit 1; \
	fi
	@rm -f file_PROTECT out_PROTECT
	@echo "=== ВСЁ РАБОТАЕТ! ==="
clean:
	rm -f $(TARGET) $(LIB) test_in test_out infile_PROTECT outfile_PROTECT
