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
    srandom(2002);
    //simple REAL test of HEAP
    HEAP *p = newHEAP(displayREAL,compareREAL,freeREAL);
    insertHEAP(p,newREAL(3));
    insertHEAP(p,newREAL(2));
    insertHEAP(p,newREAL(0));
    buildHEAP(p);
    //printf("heap: ");
    //displayHEAP(p,stdout);
    //printf("\n");
    //printf("debug:\n");
    //displayHEAPdebug(p,stdout);
    printf("min should be %f\n",getREAL(peekHEAP(p)));
    REAL *r = extractHEAP(p);
    printf("min is %f\n",getREAL(r));
    freeREAL(r);
    printf("heap: ");
    //displayHEAP(p,stdout);
    //printf("\n");
    //printf("debug:\n");
    //displayHEAPdebug(p,stdout);
    printf("min should be %f\n",getREAL(peekHEAP(p)));
    r = extractHEAP(p);
    printf("min is %f\n",getREAL(r));
    freeREAL(r);
    //printf("heap: ");
    //displayHEAP(p,stdout);
    //printf("\n");
    //printf("debug:\n");
    //displayHEAPdebug(p,stdout);
    printf("peek: %f\n",getREAL(peekHEAP(p)));
    printf("size: %d\n",sizeHEAP(p));
    freeHEAP(p);
    return 0;
    }
