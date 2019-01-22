#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(6445);
    SLL *p = newSLL(displayINTEGER,freeINTEGER);
    /* do some inserts */
    int i;
    for (i = 0; i < 1000000; ++i)
        {
        int j = random() % 100;
        insertSLL(p,0,newINTEGER(j));
        }
    /* now a bunch of gets and sets */
    printf("starting 1000000 get and sets\n");
    int size = sizeSLL(p);
    for (i = 0; i < 1000000; ++i)
        {
        INTEGER *x = getSLL(p,size-1);
        setINTEGER(x,random() % 100);
        (void) setSLL(p,size-1,x);
        }
    if (sizeSLL(p) < 100)
        {
        printf("p: ");
        displaySLL(p,stdout);
        printf("\n");
        printf("p (debug): ");
        displaySLLdebug(p,stdout);
        printf("\n");
        printf("\n");
        }
    printf("size of p is %d\n",sizeSLL(p));
    printf("the last value is %d\n",getINTEGER(getSLL(p,size-1)));
    freeSLL(p);
    return 0;
    }
