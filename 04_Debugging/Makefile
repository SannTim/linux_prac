CC = gcc
CFLAGS = -O0 -g -Wall
TARGET = prog

all: $(TARGET)

$(TARGET): prog.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(TARGET)
	@echo "Running test 1..."
	@gdb --batch --quiet -x gdb_script1.gdb 2>/dev/null | grep "^@@@" > output1.txt
	@echo "Running test 2..."
	@gdb --batch --quiet -x gdb_script2.gdb 2>/dev/null | grep "^@@@" > output2.txt

	@if cmp -s output1.txt expected1.txt; then \
		echo "Test 1: OK"; \
	else \
		echo "Test 1: FAILED"; \
		echo "Expected:"; cat expected1.txt; \
		echo "Got:"; cat output1.txt; \
	fi

	@if cmp -s output2.txt expected2.txt; then \
		echo "Test 2: OK"; \
	else \
		echo "Test 2: FAILED"; \
		echo "Expected:"; cat expected2.txt; \
		echo "Got:"; cat output2.txt; \
	fi

clean:
	rm -f $(TARGET) output1.txt output2.txt

.PHONY: all test clean
