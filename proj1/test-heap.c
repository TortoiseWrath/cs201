/*#include <stdio.h>
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

*/

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "stack.h"
#include "queue.h"
#include "heap.h"

int rcompareINTEGER(void *a, void *b) {
	return -1 * compareINTEGER(a, b);
}


extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(2013);
    //INTEGER test of HEAP
    int i;
    HEAP *p = newHEAP(displayINTEGER,rcompareINTEGER,freeINTEGER);
    for (i = 0; i < 103849; ++i)
        {
        int j = random();
        INTEGER *a = newINTEGER(j);
        insertHEAP(p,a);
        }
    buildHEAP(p);
    printf("peek: %d\n",getINTEGER(peekHEAP(p)));
    //if (sizeHEAP(p) < 200)
    //    {
    //    printf("heap: ");
    //    displayHEAP(p,stdout);
    //    printf("\n");
    //    printf("debug:\n");
    //    displayHEAPdebug(p,stdout);
    //    }
    printf("size is %d\n",sizeHEAP(p));
    for (i = 0; i < 103839; ++i)
        {
        INTEGER *x = extractHEAP(p);
        if (sizeHEAP(p) < 20)
            printf("extracted %d\n",getINTEGER(x));
        freeINTEGER(x);
        }
    printf("peek: %d\n",getINTEGER(peekHEAP(p)));
    //if (sizeHEAP(p) < 200)
    //    {
    //    printf("heap: ");
    //    displayHEAP(p,stdout);
    //    printf("\n");
    //    printf("debug:\n");
    //    displayHEAPdebug(p,stdout);
    //    }
    printf("size is %d\n",sizeHEAP(p));
    freeHEAP(p);
    return 0;
    }
