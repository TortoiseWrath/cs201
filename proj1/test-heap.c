#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "integer.h"

int rcompareINTEGER(void *a, void *b) {
	return -1 * compareINTEGER(a, b);
}

int main() {
	HEAP *t = newHEAP(displayINTEGER, compareINTEGER, freeINTEGER);
	displayHEAP(t, stdout);
	fputc('\n',stdout);
	displayHEAPdebug(t, stdout);
	fputc('\n',stdout);
	INTEGER *x = newINTEGER(68);
	insertHEAP(t, x);
	x = newINTEGER(54);
	insertHEAP(t, x);
	x = newINTEGER(53);
	displayHEAP(t, stdout);
	fputc('\n',stdout);
	displayHEAPdebug(t, stdout);
	fputc('\n',stdout);
	insertHEAP(t, x);
	displayHEAP(t, stdout);
	fputc('\n',stdout);
	displayHEAPdebug(t, stdout);
	fputc('\n',stdout);
	x = newINTEGER(45);
	insertHEAP(t, x);
	x = newINTEGER(48);
	insertHEAP(t, x);
	x = newINTEGER(50);
	insertHEAP(t, x);
	x = newINTEGER(55);
	insertHEAP(t, x);
	x = newINTEGER(74);
	insertHEAP(t, x);
	x = newINTEGER(70);
	insertHEAP(t, x);
	x = newINTEGER(75);
	insertHEAP(t, x);
	x = newINTEGER(80);
	insertHEAP(t, x);
	displayHEAP(t, stdout);
	fputc('\n',stdout);
	displayHEAPdebug(t, stdout);
	fputc('\n',stdout);

	buildHEAP(t);
	displayHEAP(t, stdout);
	fputc('\n', stdout);
	displayHEAPdebug(t, stdout);
	fputc('\n', stdout);

	displayINTEGER(peekHEAP(t), stdout);
	fputc('\n', stdout);

	x = extractHEAP(t);
	displayINTEGER(x, stdout);
	fputc('\n', stdout);
	displayHEAP(t, stdout);
	fputc('\n', stdout);
	displayHEAPdebug(t, stdout);
	fputc('\n', stdout);
	freeINTEGER(x);

	x = extractHEAP(t);
	displayINTEGER(x, stdout);
	fputc('\n', stdout);
	displayHEAP(t, stdout);
	fputc('\n', stdout);
	displayHEAPdebug(t, stdout);
	fputc('\n', stdout);

	displayINTEGER(peekHEAP(t), stdout);
	fputc('\n', stdout);

	freeHEAP(t);
	freeINTEGER(x);
	return 0;
}
