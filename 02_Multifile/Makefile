GENERATES = prog README liboutput_static.a liboutput.so
TRASH = *.o *~ o.*
CFLAGS = -Wall -Wextra -Werror -fPIC
LIBRARY_DEPENDENCY = fun.o const.o

%.o: %.c
	cc $(CFLAGS) $< -c -o $@

liboutput_static.a: $(LIBRARY_DEPENDENCY)
	ar -rcs $@ $^

liboutput.so: $(LIBRARY_DEPENDENCY)
	cc -shared $^ -o $@ 


all: README prog

prog: const.o fun.o prog.o 
	cc $^ -o $@

fun.o: outlib.h

README: prog
	./$< 2> $@

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
