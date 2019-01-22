#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "real.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(3932);
    SLL *p = newSLL(displayREAL,freeREAL);
    insertSLL(p,0,newREAL(3.3));
    insertSLL(p,sizeSLL(p),newREAL(2.2));
    displaySLL(p,stdout);
    printf("\n");
    freeREAL(removeSLL(p,1));
    displaySLL(p,stdout);
    printf("\n");
    freeREAL(removeSLL(p,0));
    displaySLL(p,stdout);
    printf("\n");
    SLL *q = newSLL(displayREAL,freeREAL);
    insertSLL(p,0,newREAL(6.7));
    insertSLL(p,0,newREAL(8.9));
    insertSLL(q,0,newREAL(4.3));
    insertSLL(q,0,newREAL(5.2));
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
