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
    srandom(2003);
    //simple STRING test of HEAP
    HEAP *p = newHEAP(displaySTRING,compareSTRING,freeSTRING);
    insertHEAP(p,newSTRING("a3"));
    insertHEAP(p,newSTRING("a0"));
    insertHEAP(p,newSTRING("a2"));
    buildHEAP(p);
    //printf("heap: ");
    //displayHEAP(p,stdout);
    //printf("\n");
    //printf("debug:\n");
    //displayHEAPdebug(p,stdout);
    printf("min should be %s\n",getSTRING(peekHEAP(p)));
    STRING *r = extractHEAP(p);
    printf("min is %s\n",getSTRING(r));
    freeSTRING(r);
    //printf("heap: ");
    //displayHEAP(p,stdout);
    //printf("\n");
    //printf("debug:\n");
    //displayHEAPdebug(p,stdout);
    printf("min should be %s\n",getSTRING(peekHEAP(p)));
    r = extractHEAP(p);
    printf("min is %s\n",getSTRING(r));
    freeSTRING(r);
    //printf("heap: ");
    //displayHEAP(p,stdout);
    //printf("\n");
    //printf("debug:\n");
    //displayHEAPdebug(p,stdout);
    printf("peek: %s\n",getSTRING(peekHEAP(p)));
    printf("size: %d\n",sizeHEAP(p));
    freeHEAP(p);
    return 0;
    }
