OBJS = test-sll test-dll test-queue test-bst test-avl test-binomial prim binomial.o dll.o sll.o queue.o avl.o bst.o integer.o scanner.o vertex.o edge.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : tests prim
tests : test-avl test-binomial test-bst test-dll test-queue test-sll

test-bst : test-bst.c bst.o queue.o sll.o integer.o
	gcc $(LOPTS) test-bst.c bst.o queue.o sll.o integer.o -o test-bst

test-avl : test-avl.c avl.o bst.o queue.o sll.o integer.o
	gcc $(LOPTS) test-avl.c avl.o bst.o queue.o sll.o integer.o -o test-avl

test-sll : test-sll.c sll.o integer.o
	gcc $(LOPTS) test-sll.c sll.o integer.o -o test-sll

test-dll : test-dll.c dll.o integer.o
	gcc $(LOPTS) test-dll.c dll.o integer.o -o test-dll

test-queue : test-queue.c queue.o sll.o integer.o integer.o
	gcc $(LOPTS) test-queue.c queue.o sll.o integer.o -o test-queue

test-binomial : test-binomial.c binomial.o dll.o integer.o queue.o sll.o
	gcc $(LOPTS) test-binomial.c binomial.o dll.o integer.o queue.o sll.o -o test-binomial -lm

prim : prim.c scanner.o edge.o vertex.o avl.o queue.o dll.o sll.o binomial.o bst.o integer.o
	gcc $(LOPTS) prim.c scanner.o edge.o vertex.o avl.o queue.o dll.o sll.o bst.o binomial.o integer.o -o prim -lm


binomial.o: binomial.c binomial.h dll.o queue.o
	gcc $(OOPTS) binomial.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

queue.o : queue.c queue.h sll.o
	gcc $(OOPTS) queue.c

avl.o: avl.c avl.h bst.o
	gcc $(OOPTS) avl.c

bst.o : bst.c bst.h queue.h
	gcc $(OOPTS) bst.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

vertex.o : vertex.c vertex.h dll.o
	gcc $(OOPTS) vertex.c

edge.o : edge.c edge.h
	gcc $(OOPTS) edge.c

valgrind  : all
	echo testing SLL
	valgrind ./test-sll
	echo testing DLL
	valgrind ./test-dll
	echo testing queue
	valgrind ./test-queue
	echo testing BST
	valgrind ./test-bst
	echo testing AVL
	valgrind ./test-avl
	echo testing binomial heap
	valgrind ./test-binomial
	echo testing prim
	valgrind ./prim prim.data
	echo

test : all
	echo testing SLL
	./test-sll
	echo testing DLL
	./test-dll
	echo testing queue
	./test-queue
	echo testing BST
	./test-bst
	echo testing AVL
	./test-avl
	echo testing binomial heap
	./test-binomial
	echo testing prim
	./prim prim.data
	echo

clean    :
	rm -f $(OBJS)
