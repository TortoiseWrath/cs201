OBJS = integer.o test-integer.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : test-integer

test-integer : $(OBJS)
		gcc $(LOPTS) $(OBJS) -o test-integer

integer.o : integer.c integer.h
		gcc $(OOPTS) integer.c

test-integer.o :	test-integer.c integer.h
		gcc $(OOPTS) test-integer.c

test : test-integer
		./test-integer

valgrind : test-integer
		valgrind test-integer

clean	:
		rm -f $(OBJS) test-integer
