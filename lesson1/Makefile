CFLAGS := -Wall -Wextra -g $(shell pkg-config --cflags ncursesw)
LDLIBS := $(shell pkg-config --libs ncursesw)

all: a.out

a.out: 3.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f a.out

