OBJS = bst.o queue.o sll.o integer.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : tests heapsort
tests : test-bst test-heap

heapsort : heapsort.c scanner.o heap.o bst.o queue.o stack.o sll.o dll.o integer.o string.o real.o
	gcc $(LOPTS) heapsort.c scanner.o heap.o bst.o queue.o stack.o sll.o dll.o integer.o string.o real.o -o heapsort

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

string.o : string.c string.h
	gcc $(OOPTS) string.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

valgrind  : all
	echo testing BST
	valgrind ./test-bst
	echo testing heap
	valgrind ./test-heap
	echo 14249 27449 4191 895 3099 27455 9417 14345 22817 17045 > data
	cat data
	echo testing heapsort
	valgrind ./heapsort data
	valgrind ./heapsort -D data
	valgrind ./heapsort -I -i data
	valgrind ./heapsort -v
	rm data
	echo

test : all
	echo testing BST
	./test-bst
	echo testing heap
	./test-heap
	echo 14249 27449 4191 895 3099 27455 9417 14345 22817 17045 > data
	cat data
	echo testing heapsort
	./heapsort data
	./heapsort -D data
	./heapsort -I -i data
	./heapsort -v
	rm data
	echo

clean    :
	rm -f $(OBJS) *.o test-bst test-heap heapsort data
