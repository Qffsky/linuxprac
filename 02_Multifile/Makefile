GENERATES = prog prog-a prog-so README liboutput_static.a liboutput.so
TRASH = *.o *~ o.*
CFLAGS = -Wall -Wextra -Werror -fPIC
LIBRARY_DEPENDENCY = fun.o const.o
OBJS = fun.o const.o prog.o

%.o: %.c
	cc $(CFLAGS) $< -c -o $@

liboutput_static.a: $(LIBRARY_DEPENDENCY)
	ar -rcs $@ $^

liboutput.so: $(LIBRARY_DEPENDENCY)
	cc $(CFLAGS) -shared $^ -o $@ 


all: README prog

prog: $(OBJS)
	cc $(CFLAGS) $^ -o $@

prog-a: prog.o liboutput_static.a
	cc $(CFLAGS) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc $(CFLAGS) -L. $< -loutput -o $@

fun.o: outlib.h

README: prog
	./$< 2> $@

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
