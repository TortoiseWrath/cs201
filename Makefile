OBJS = integer.o sll.o dll.o stack.o queue.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : test-sll test-dll test-stack test-queue

test-sll : test-sll.c sll.o integer.o integer.o
	gcc $(LOPTS) test-sll.c sll.o integer.o -o test-sll

test-dll : test-dll.c dll.o integer.o integer.o
	gcc $(LOPTS) test-dll.c dll.o integer.o -o test-dll

test-stack : test-stack.c stack.o sll.o integer.o integer.o
	gcc $(LOPTS) test-stack.c stack.o sll.o integer.o -o test-stack

test-queue : test-queue.c queue.o dll.o integer.o integer.o
	gcc $(LOPTS) test-queue.c queue.o dll.o integer.o -o test-queue



stack.o : stack.c stack.h sll.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h dll.h
	gcc $(OOPTS) queue.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

valgrind  : all
	echo testing singly-linked list
	valgrind ./test-sll
	echo
	echo testing doubly-linked list
	valgrind ./test-dll
	echo
	echo testing stack
	valgrind ./test-stack
	echo
	echo testing queue
	valgrind ./test-queue
	echo

test : all
	echo testing singly-linked list
	./test-sll
	echo
	echo testing doubly-linked list
	./test-dll
	echo
	echo testing stack
	./test-stack
	echo
	echo testing queue
	./test-queue
	echo

clean    :
	rm -f $(OBJS) test-*.o test-stack test-queue test-sll test-dll
