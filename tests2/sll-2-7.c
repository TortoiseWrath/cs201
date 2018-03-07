#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(1145);
    SLL *p = newSLL(displayINTEGER,freeINTEGER);
    SLL *q = newSLL(displayINTEGER,freeINTEGER);
    unionSLL(p,q);
    /* do some inserts */
    int i;
    for (i = 0; i < 20; ++i)
        {
        int j = random() % 100;
        insertSLL(p,0,newINTEGER(j));
        }
    /* do some inserts */
    for (i = 0; i < 20; ++i)
        {
        int j = random() % 100;
        insertSLL(q,0,newINTEGER(j));
        }
    /* now a bunch of unions */
    printf("starting 1000000 unions\n");
    for (i = 0; i < 1000000; ++i)
        {
        unionSLL(q,p);
        unionSLL(p,q);
        }
    /* do some inserts */
    for (i = 0; i < 170; ++i)
        {
        int j = random() % 100;
        insertSLL(p,0,newINTEGER(j));
        j = random() % 100;
        insertSLL(q,0,newINTEGER(j));
        }
    if (sizeSLL(p) < 200)
        {
        printf("p: ");
        displaySLL(p,stdout);
        printf("\n");
        printf("p (debug): ");
        displaySLLdebug(p,stdout);
        printf("\n");
        printf("\n");
        }
    if (sizeSLL(q) < 200)
        {
        printf("q: ");
        displaySLL(q,stdout);
        printf("\n");
        printf("q (debug): ");
        displaySLLdebug(q,stdout);
        printf("\n");
        printf("\n");
        }
    if (sizeSLL(p) > 0)
        {
        i = random() % sizeSLL(p);
        int value = random() % 100;
        printf("size is %d\n",sizeSLL(p));
        printf("value at %d is %d\n",i,getINTEGER(getSLL(p,i)));
        printf("setting value at %d to %d\n",i,value);
        freeINTEGER(setSLL(p,i,newINTEGER(value)));
        printf("value at %d now is %d\n",i,getINTEGER(getSLL(p,i)));
        }
    if (sizeSLL(q) > 0)
        {
        i = random() % sizeSLL(q);
        int value = random() % 100;
        printf("size is %d\n",sizeSLL(q));
        printf("value at %d is %d\n",i,getINTEGER(getSLL(q,i)));
        printf("setting value at %d to %d\n",i,value);
        freeINTEGER(setSLL(q,i,newINTEGER(value)));
        printf("value at %d now is %d\n",i,getINTEGER(getSLL(q,i)));
        }
    freeSLL(p);
    freeSLL(q);
    return 0;
    }
