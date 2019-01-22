#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "integer.h"

static void showItems(QUEUE *items) {
	printf("The items are ");
	displayQUEUE(items,stdout);
	printf(".\n");
	printf("The items (debugged) are ");
	displayQUEUEdebug(items,stdout);
	printf(".\n");
}


int main() {
	QUEUE *items = newQUEUE(displayINTEGER, freeINTEGER);
	showItems(items); // <>

	INTEGER *x = newINTEGER(5);
	enqueue(items, x);
	showItems(items); // <5>

	setINTEGER(x, 77);
	showItems(items); // <77>
	x = dequeue(items);
	displayINTEGER(x, stdout); // 77
	freeINTEGER(x);
	putc('\n', stdout);
	showItems(items); // <>

	x = newINTEGER(1232);
	enqueue(items, x);
	x = newINTEGER(78);
	enqueue(items, x);
	x = newINTEGER(111);
	enqueue(items, x);
	x = newINTEGER(19);
	enqueue(items, x);
	x = newINTEGER(3);
	enqueue(items, x);
	x = newINTEGER(68);
	enqueue(items, x);
	x = newINTEGER(-4);
	enqueue(items, x);
	x = newINTEGER(6);
	enqueue(items, x);
	showItems(items); // <1232,78,111,19,3,68,-4,6>

	displayINTEGER(peekQUEUE(items), stdout); // 1232
	putc('\n', stdout);
	x = dequeue(items);
	displayINTEGER(x, stdout); // 1232
	freeINTEGER(x);
	putc('\n', stdout);
	showItems(items); // <78,111,19,3,68,-4,6>

	freeQUEUE(items);
	return 0;
}
