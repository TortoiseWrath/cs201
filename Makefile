OBJS = bst.o queue.o sll.o integer.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : tests
tests : test-gst test-avl

test-bst : test-bst.c bst.o queue.o sll.o integer.o
	gcc $(LOPTS) test-bst.c bst.o queue.o sll.o integer.o -o test-bst

test-gst : test-gst.c gst.o bst.o queue.o sll.o integer.o
	gcc $(LOPTS) test-gst.c gst.o bst.o queue.o sll.o integer.o -o test-gst

test-avl : test-avl.c avl.o bst.o queue.o sll.o integer.o
	gcc $(LOPTS) test-avl.c avl.o bst.o queue.o sll.o integer.o -o test-avl


gst.o: gst.c gst.h bst.o
	gcc $(OOPTS) gst.c

avl.o: avl.c avl.h bst.o
	gcc $(OOPTS) avl.c

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

string.o : string.c string.h
	gcc $(OOPTS) string.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

valgrind  : all
	echo testing GST
	valgrind ./test-gst
	echo testing AVL
	valgrind ./test-avl
	echo

test : all
	echo testing GST
	./test-gst
	echo testing AVL
	./test-avl
	echo

clean    :
	rm -f $(OBJS) *.o test-gst
