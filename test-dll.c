#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "integer.h"

static void showItems(DLL *items) {
	printf("The items are ");
	displayDLL(items,stdout);
	printf(".\n");
	printf("The items (debugged) are ");
	displayDLLdebug(items,stdout);
	printf(".\n");
}


int main() {
	DLL *items2 = newDLL(displayINTEGER, freeINTEGER);
	showItems(items2);
	INTEGER *x = newINTEGER(0);
	insertDLL(items2,0,x); //0
	x = newINTEGER(1232);
	insertDLL(items2,0,x); //1232 0
	x = newINTEGER(78);
	insertDLL(items2,2,x); //1232 0 78
	x = newINTEGER(111);
	insertDLL(items2,3,x); //1232 0 78 111
	x = newINTEGER(19);
	insertDLL(items2,3,x); //1232 0 78 19 111
	x = newINTEGER(3);
	insertDLL(items2,2,x); //1232 0 3 78 19 111
	x = newINTEGER(68);
	setDLL(items2,1,x); //1232 68 3 78 19 111
	x = newINTEGER(-4);
	setDLL(items2,4,x); //1232 68 3 78 -4 111
	x = newINTEGER(6);
	setDLL(items2,6,x); //1232 68 3 78 -4 111 6
	showItems(items2);
	setINTEGER(x, 30); //1232 68 3 78 -4 111 30
	showItems(items2);
	displayINTEGER(removeDLL(items2,2), stdout); //3
	putc('\n', stdout);
	displayINTEGER(removeDLL(items2,5), stdout); //30
	putc('\n', stdout);
	displayINTEGER(removeDLL(items2,3), stdout); //-4
	putc('\n', stdout);
	showItems(items2); //1232 68 78 111
	displayINTEGER(getDLL(items2,3), stdout); //111
	putc('\n', stdout);
	displayINTEGER(getDLL(items2,1), stdout); //68
	putc('\n', stdout);
	displayINTEGER(getDLL(items2,0), stdout); //1232
	putc('\n', stdout);
	freeDLL(items2);

	return 0;
}
