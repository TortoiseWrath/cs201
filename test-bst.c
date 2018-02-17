#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"


int main() {
	BST *t = newBST(displayINTEGER, compareINTEGER, NULL, freeINTEGER);
	displayBST(t);
	displayBSTdebug(t);
	INTEGER *x = newInteger(68);
	insertBST(t, x);
	INTEGER *x = newInteger(54);
	insertBST(t, x);
	INTEGER *x = newInteger(53);
	insertBST(t, x);
	INTEGER *x = newInteger(45);
	insertBST(t, x);
	INTEGER *x = newInteger(48);
	insertBST(t, x);
	INTEGER *x = newInteger(50);
	insertBST(t, x);
	INTEGER *x = newInteger(55);
	insertBST(t, x);
	INTEGER *x = newInteger(74);
	insertBST(t, x);
	INTEGER *x = newInteger(70);
	insertBST(t, x);
	INTEGER *x = newInteger(75);
	insertBST(t, x);
	INTEGER *x = newInteger(80);
	insertBST(t, x);
	displayBST(t);
	displayBSTdebug(t);
	freeBST(t);
	return 0;
}
