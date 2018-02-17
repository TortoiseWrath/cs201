#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"


int main() {
	BST *t = newBST(displayINTEGER, compareINTEGER, NULL, freeINTEGER);
	displayBST(t, stdout);
	fputc('\n',stdout);
	displayBSTdebug(t, stdout);
	fputc('\n',stdout);
	INTEGER *x = newINTEGER(68);
	insertBST(t, x);
	x = newINTEGER(54);
	insertBST(t, x);
	x = newINTEGER(53);
	insertBST(t, x);
	x = newINTEGER(45);
	insertBST(t, x);
	x = newINTEGER(48);
	insertBST(t, x);
	x = newINTEGER(50);
	insertBST(t, x);
	x = newINTEGER(55);
	insertBST(t, x);
	x = newINTEGER(74);
	insertBST(t, x);
	x = newINTEGER(70);
	insertBST(t, x);
	x = newINTEGER(75);
	insertBST(t, x);
	x = newINTEGER(80);
	insertBST(t, x);
	displayBST(t, stdout);
	fputc('\n',stdout);
	displayBSTdebug(t, stdout);
	fputc('\n',stdout);
	freeBST(t);
	return 0;
}
