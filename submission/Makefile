OBJS = bst.o queue.o sll.o integer.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : tests
tests : test-gst

test-bst : test-bst.c bst.o queue.o sll.o integer.o
	gcc $(LOPTS) test-bst.c bst.o queue.o sll.o integer.o -o test-bst

test-gst : test-gst.c gst.o bst.o queue.o sll.o integer.o
	gcc $(LOPTS) test-gst.c gst.o bst.o queue.o sll.o integer.o -o test-gst


gst.o: gst.c gst.h bst.o
	gcc $(OOPTS) gst.c

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
	echo

test : all
	echo testing GST
	./test-gst
	echo

clean    :
	rm -f $(OBJS) *.o test-gst
