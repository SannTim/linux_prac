CC = cc
CFLAGS = -g -O0 -Wall -Wextra
TARGET = esub
SRCS = esub.c

GDB_TESTS = test1.gdb test2.gdb test3.gdb test4.gdb test5.gdb

.PHONY: all clean test full-test

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $<

# Проверяем, что .gdb файлы существуют
$(GDB_TESTS):
	@if [ ! -f $@ ]; then \
		echo "ERROR: $@ not found. Create it manually."; \
		exit 1; \
	fi

test: $(TARGET) $(GDB_TESTS)
	@for t in $(GDB_TESTS); do \
		echo "Running $$t..."; \
		gdb --batch -x "$$t" ./$(TARGET) 2>/dev/null | grep -E "FAIL|OK" || true; \
	done


full-test: check-returns test

clean:
	rm -f $(TARGET)

