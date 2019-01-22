#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "integer.h"

static void showItems(STACK *items) {
	printf("The items are ");
	displaySTACK(items,stdout);
	printf(".\n");
	printf("The items (debugged) are ");
	displaySTACKdebug(items,stdout);
	printf(".\n");
}


int main() {
	STACK *items = newSTACK(displayINTEGER, freeINTEGER);
	showItems(items); // ||

	INTEGER *x = newINTEGER(5);
	push(items, x);
	showItems(items); // |5|

	setINTEGER(x, 77);
	showItems(items); // |77|
	x = pop(items);
	displayINTEGER(x, stdout); // 77
	freeINTEGER(x);
	putc('\n', stdout);
	showItems(items); // ||

	x = newINTEGER(1232);
	push(items, x);
	x = newINTEGER(78);
	push(items, x);
	x = newINTEGER(111);
	push(items, x);
	x = newINTEGER(19);
	push(items, x);
	x = newINTEGER(3);
	push(items, x);
	x = newINTEGER(68);
	push(items, x);
	x = newINTEGER(-4);
	push(items, x);
	x = newINTEGER(6);
	push(items, x);
	showItems(items); // |6,-4,68,3,19,111,78,1232|

	displayINTEGER(peekSTACK(items), stdout); // 6
	putc('\n', stdout);
	x = pop(items);
	displayINTEGER(x, stdout); // 6
	freeINTEGER(x);
	putc('\n', stdout);
	showItems(items); // |-4,68,3,19,111,78,1232|

	freeSTACK(items);
	return 0;
}
