#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "stack.h"
#include "queue.h"
#include "heap.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(1);
    //simple INTEGER test of HEAP
    HEAP *p = newHEAP(displayINTEGER,compareINTEGER,freeINTEGER);
    insertHEAP(p,newINTEGER(3));
    insertHEAP(p,newINTEGER(0));
    insertHEAP(p,newINTEGER(2));
    buildHEAP(p);
    printf("heap: ");
    displayHEAP(p,stdout);
    printf("\n");
    printf("debug:\n");
    displayHEAPdebug(p,stdout);
    printf("min should be %d\n",getINTEGER(peekHEAP(p)));
    INTEGER *r = extractHEAP(p);
    printf("min is %d\n",getINTEGER(r));
    freeINTEGER(r);
    printf("heap: ");
    displayHEAP(p,stdout);
    printf("\n");
    printf("debug:\n");
    displayHEAPdebug(p,stdout);
    printf("min should be %d\n",getINTEGER(peekHEAP(p)));
    r = extractHEAP(p);
    printf("min is %d\n",getINTEGER(r));
    freeINTEGER(r);
    printf("heap: ");
    displayHEAP(p,stdout);
    printf("\n");
    printf("debug:\n");
    displayHEAPdebug(p,stdout);
    printf("peek: %d\n",getINTEGER(peekHEAP(p)));
    printf("size: %d\n",sizeHEAP(p));
    freeHEAP(p);
    return 0;
    }
