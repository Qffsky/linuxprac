LIBRARIES = liboutput_static.a liboutput.so
EXECUTABLES = prog prog-a prog-so
DOCS = README
GENERATES = $(EXECUTABLES) $(LIBRARIES) $(DOCS)
TRASH = *.o *~ o.*
CFLAGS = -Wall -Wextra -Werror -fPIC
LIBRARY_DEPENDENCY = fun.o const.o
OBJS = fun.o const.o prog.o
TEST_ZERO_REFERENCE = test/reference/zero-parameter.txt
TEST_ONE_REFERENCE = test/reference/one-parameter.txt
TEST_ONE_INPUT = parameter
TEST_THREE_REFERENCE = test/reference/three-parameter.txt
TEST_THREE_INPUT = one two three

TEST_DIR = test
TEST_DIR_SCRIPTS = $(TEST_DIR)/scripts
TEST_DIR_WITHOUT = $(TEST_DIR)/without
TEST_DIR_ONE = $(TEST_DIR)/one
TEST_DIR_THREE = $(TEST_DIR)/three
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
	$(LD_PATH) ./$(EXEC) $(TEST_ONE_INPUT) > $(TEST_DIR_ONE)/$(EXEC).txt

%-test-three: % $(TEST_DIR_THREE)
	$(LD_PATH) ./$(EXEC) $(TEST_THREE_INPUT) > $(TEST_DIR_THREE)/$(EXEC).txt

test-simple: $(addsuffix -test-simple, $(EXECUTABLES))
	@echo CHECKING ZERO ARGS
	$(TEST_DIR_SCRIPTS)/check.sh $(TEST_ZERO_REFERENCE) $(TEST_DIR_WITHOUT)/prog.txt $(TEST_DIR_WITHOUT)/prog-a.txt $(TEST_DIR_WITHOUT)/prog-so.txt 

test-three: $(addsuffix -test-three, $(EXECUTABLES))
	@echo CHECKING THREE ARGS
	$(TEST_DIR_SCRIPTS)/check.sh $(TEST_THREE_REFERENCE) $(TEST_DIR_THREE)/prog.txt $(TEST_DIR_THREE)/prog-a.txt $(TEST_DIR_THREE)/prog-so.txt 

test-one: $(addsuffix -test-one, $(EXECUTABLES))
	@echo CHECKING ONE ARG
	$(TEST_DIR_SCRIPTS)/check.sh $(TEST_ONE_REFERENCE) $(TEST_DIR_ONE)/prog.txt $(TEST_DIR_ONE)/prog-a.txt $(TEST_DIR_ONE)/prog-so.txt 

test: test-simple test-one test-three

README: prog
	./$< 2> $@

clean-test: 
	rm -rf $(TEST_DIRS)

clean: clean-test
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
