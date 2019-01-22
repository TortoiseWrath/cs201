#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "string.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(7750);
    SLL *p = newSLL(displaySTRING,freeSTRING);
    insertSLL(p,0,newSTRING("a"));
    insertSLL(p,sizeSLL(p),newSTRING("b"));
    displaySLL(p,stdout);
    printf("\n");
    freeSTRING(removeSLL(p,1));
    displaySLL(p,stdout);
    printf("\n");
    freeSTRING(removeSLL(p,0));
    displaySLL(p,stdout);
    printf("\n");
    SLL *q = newSLL(displaySTRING,freeSTRING);
    insertSLL(p,0,newSTRING("e"));
    insertSLL(p,0,newSTRING("f"));
    insertSLL(q,0,newSTRING("c"));
    insertSLL(q,0,newSTRING("d"));
    displaySLL(p,stdout);
    printf("\n");
    displaySLL(q,stdout);
    printf("\n");
    unionSLL(p,q);
    displaySLL(p,stdout);
    displaySLL(q,stdout);
    printf("\n");
    displaySLLdebug(p,stdout);
    printf("\n");
    displaySLLdebug(q,stdout);
    printf("\n");
    freeSLL(p);
    freeSLL(q);
    return 0;
    }
