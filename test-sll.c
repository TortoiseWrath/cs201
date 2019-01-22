#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

static void showItems(SLL *items) {
	printf("The items are ");
	displaySLL(items,stdout);
	printf(".\n");
	printf("The items (debugged) are ");
	displaySLLdebug(items,stdout);
	printf(".\n");
}


int main() {
	SLL *items2 = newSLL(displayINTEGER, freeINTEGER);
	showItems(items2);

	INTEGER *x = newINTEGER(0);
	insertSLL(items2,0,x); //0
	x = newINTEGER(1232);
	insertSLL(items2,0,x); //1232 0
	x = newINTEGER(78);
	insertSLL(items2,2,x); //1232 0 78
	x = newINTEGER(111);
	insertSLL(items2,3,x); //1232 0 78 111
	x = newINTEGER(19);
	insertSLL(items2,3,x); //1232 0 78 19 111
	x = newINTEGER(3);
	insertSLL(items2,2,x); //1232 0 3 78 19 111
	x = newINTEGER(68);
	freeINTEGER(setSLL(items2,1,x)); //1232 68 3 78 19 111
	x = newINTEGER(-4);
	freeINTEGER(setSLL(items2,4,x)); //1232 68 3 78 -4 111
	x = newINTEGER(6);
	freeINTEGER(setSLL(items2,6,x)); //1232 68 3 78 -4 111 6
	showItems(items2);
	setINTEGER(x, 30); //1232 68 3 78 -4 111 30
	showItems(items2);
	x = removeSLL(items2,2);
	displayINTEGER(x, stdout); //3
	freeINTEGER(x);
	putc('\n', stdout);

	x = removeSLL(items2,5);
	displayINTEGER(x, stdout); //30
	freeINTEGER(x);
	putc('\n', stdout);
	x = removeSLL(items2,3);
	displayINTEGER(x, stdout); //3-4
	freeINTEGER(x);
	putc('\n', stdout);
	showItems(items2); //1232 68 78 111
	displayINTEGER(getSLL(items2,3), stdout); //111
	putc('\n', stdout);
	displayINTEGER(getSLL(items2,1), stdout); //68
	putc('\n', stdout);
	displayINTEGER(getSLL(items2,0), stdout); //1232
	putc('\n', stdout);


	freeSLL(items2);

	return 0;
}
