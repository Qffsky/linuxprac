LIBRARIES = liboutput_static.a liboutput.so
EXECUTABLES = prog prog-a prog-so
DOCS = README
GENERATES = $(EXECUTABLES) $(LIBRARIES) $(DOCS)
TRASH = *.o *~ o.*
CFLAGS = -Wall -Wextra -Werror -fPIC
LIBRARY_DEPENDENCY = fun.o const.o
OBJS = fun.o const.o prog.o
TEST_ONE = test/reference/one-parameter.txt
TEST_THREE = test/reference/three-parameter.txt

TEST_DIR_WITHOUT = test/without
TEST_DIR_ONE = test/one
TEST_DIR_THREE = test/three
TEST_DIRS = $(TEST_DIR_WITHOUT) $(TEST_DIR_ONE) $(TEST_DIR_THREE)

all: $(GENERATES)

%.o: %.c
	cc $(CFLAGS) $< -c -o $@

liboutput_static.a: $(LIBRARY_DEPENDENCY)
	ar -rcs $@ $^

liboutput.so: $(LIBRARY_DEPENDENCY)
	cc $(CFLAGS) -shared $^ -o $@ 

prog: $(OBJS)
	cc $(CFLAGS) $^ -o $@

prog-a: prog.o liboutput_static.a
	cc $(CFLAGS) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc $(CFLAGS) -L. $< -loutput -o $@

fun.o: outlib.h

$(TEST_DIRS):
	mkdir $@

prog-test-%:    EXEC = prog
prog-a-test-%:  EXEC = prog-a
prog-so-test-%: EXEC = prog-so
prog-so-test-%: LD_PATH = LD_LIBRARY_PATH=`pwd`



%-test-simple: % $(TEST_DIR_WITHOUT)
	$(LD_PATH) ./$(EXEC) 2> $(TEST_DIR_WITHOUT)/$(EXEC).txt

%-test-one: % $(TEST_DIR_ONE)
	$(LD_PATH) ./$(EXEC) 2> $(TEST_DIR_ONE)/$(EXEC).txt < $(TEST_ONE)

%-test-three: % $(TEST_DIR_THREE)
	$(LD_PATH) ./$(EXEC) 2> $(TEST_DIR_THREE)/$(EXEC).txt < $(TEST_THREE)

test-simple: $(addsuffix -test-simple, $(EXECUTABLES))

test-one: $(addsuffix -test-one, $(EXECUTABLES))

test-three: $(addsuffix -test-three, $(EXECUTABLES))

test: test-simple test-one test-three

README: prog
	./$< 2> $@

clean-test: 
	rm -rf $(TEST_DIRS)

clean: clean-test
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
