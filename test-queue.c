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
	showItems(items); // ||

	INTEGER *x = newINTEGER(5);
	enqueue(items, x);
	showItems(items); // |5|

	setINTEGER(x, 77);
	showItems(items); // |77|
	displayINTEGER(dequeue(items), stdout); // 77
	putc('\n', stdout);
	showItems(items); // ||

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
	showItems(items); // |6,-4,68,3,19,111,78,1232|

	displayINTEGER(peekQUEUE(items), stdout); // 6
	putc('\n', stdout);
	displayINTEGER(dequeue(items), stdout); // 6
	putc('\n', stdout);
	showItems(items); // |-4,68,3,19,111,78,1232|

	freeSTACK(items);
	return 0;
}
