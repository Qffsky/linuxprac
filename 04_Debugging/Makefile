CFLAGS=-Wall -Wextra -O0 -g
TEST_SIMPLE_OUT=simple.out
TEST_ANOTHER_OUT=another.out
TEST_OUT=simple.out another.out
GENERATES=$(TEST_OUT) range
all: range

range: rangeClass.o range.o
	cc $(CFLAGS) -o $@ $^

test: range
	@gdb --command=simple.gdb --quiet --batch --args ./range 1 12 | grep @@@ > $(TEST_SIMPLE_OUT) | cmp -s - $(TEST_SIMPLE_OUT) && echo simple test terminated successfully || echo simple test have failed
	@gdb --command=another.gdb --quiet --batch --args ./range -100 100 3 2>/dev/null | grep @@@ > $(TEST_ANOTHER_OUT) | cmp -s - $(TEST_ANOTHER_OUT) && echo another test terminated successfully || echo another test have failed

clean:
	rm -rf *.o $(GENERATES)
