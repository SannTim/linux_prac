# Д/З N2
.PHONY: all clean
CFLAGS = -Wall -fPIC
GENERATES = prog prog-so prog-a 
TRASH = *.o *~ o.* *.so *.a *.output
%.o:	%.c
	cc $(CFLAGS) $< -c -o $@

all: $(GENERATES)

liboutput_static.a: const.o fun.o
	ar rcs liboutput_static.a fun.o const.o

liboutput.so: const.o fun.o
	cc -shared -o liboutput.so fun.o const.o

prog: const.o prog.o fun.o
	cc const.o fun.o prog.o -o prog

prog-a: prog.o liboutput_static.a
	cc prog.o -L. -loutput_static -o prog-a

prog-so: prog.o liboutput.so
	cc prog.o -L. -loutput -o prog-so

test: $(GENERATES)
	for num in $(GENERATES); do ./$$num > $$num-empty.output 2>&1; done
	for num in $(GENERATES); do ./$$num 3 > $$num-one.output 2>&1; done
	for num in $(GENERATES); do ./$$num 9 8 1 > $$num-three.output 2>&1; done
	for i in empty one three; do \
		for prog in $(GENERATES); do \
			for prog2 in $(GENERATES); do \
				if [ "$$prog" != "$$prog2" ]; \
					then \
					cmp $$prog-$$i.output $$prog2-$$i.output; \
				fi \
			done \
		done \
	done

		
clean-trash:
	rm -f $(TRASH)

clean:	clean-trash
	rm -rf $(GENERATES)
