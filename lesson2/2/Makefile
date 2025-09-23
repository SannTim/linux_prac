# prog:		const.o fun.o prog.o
# 	cc const.o fun.o prog.o -o prog
# 
# fun.o:		fun.c 
# 	cc fun.c -c -o fun.o
# 
# prog.o:		prog.c 
# 	cc prog.c -c -o prog.o
# 
# const.o:	const.c 
# 	cc const.c -c -o const.o
# 
#

.PHONY: all, clean
CFLAGS = -Wall -fPIC
GENERATES = const.o prog.o fun.o prog README
%.o:	%.c
	cc $(CFLAGS) $< -c -o $@

all: README prog

prog: const.o prog.o fun.o
	cc const.o fun.o prog.o -o prog

README: prog
	./$< 2 > $@

clean:
	rm -f prog a.out *.o README

