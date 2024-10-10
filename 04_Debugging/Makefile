CFLAGS=-Wall -Wextra -O0 -g

all: range

range: rangeClass.o range.o
	cc $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o range
