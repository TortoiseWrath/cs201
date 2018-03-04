OBJS = bst.o queue.o sll.o integer.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : test-bst test-heap

test-bst : test-bst.c bst.o queue.o sll.o integer.o
	gcc $(LOPTS) test-bst.c bst.o queue.o sll.o integer.o -o test-bst

test-heap : test-heap.c heap.o bst.o queue.o stack.o sll.o dll.o integer.o
	gcc $(LOPTS) test-heap.c heap.o bst.o queue.o stack.o sll.o dll.o integer.o -o test-heap


bst.o : bst.c bst.h queue.h
	gcc $(OOPTS) bst.c

heap.o : heap.c bst.h stack.h queue.h
	gcc $(OOPTS) heap.c

queue.o : queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

stack.o : stack.c stack.h dll.h
	gcc $(OOPTS) stack.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

valgrind  : all
	echo testing BST
	valgrind ./test-bst
	echo testing heap
	valgrind ./test-heap
	echo

test : all
	echo testing BST
	./test-bst
	echo testing heap
	./test-heap
	echo

clean    :
	rm -f $(OBJS) *.o test-bst test-heap
