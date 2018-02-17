OBJS = bst.o queue.o sll.o integer.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : test-bst

test-bst : test-bst.c bst.o queue.o sll.o integer.o
	gcc $(LOPTS) test-bst.c bst.o queue.o sll.o integer.o -o test-bst


bst.o : bst.c bst.h queue.h
	gcc $(OOPTS) bst.c

queue.o : queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

valgrind  : all
	echo testing BST
	valgrind ./test-bst
	echo

test : all
	echo testing BST
	./test-bst
	echo

clean    :
	rm -f $(OBJS) *.o test-bst
