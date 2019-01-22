#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(3879);
    DLL *p = newDLL(displayINTEGER,freeINTEGER);
    DLL *q = newDLL(displayINTEGER,freeINTEGER);
    unionDLL(p,q);
    /* do some inserts */
    int i;
    for (i = 0; i < 25; ++i)
        {
        int x = random() % (sizeDLL(p) + 1);
        int j = random() % 100;
        insertDLL(p,x,newINTEGER(j));
        }
    /* do some inserts */
    for (i = 0; i < 25; ++i)
        {
        int x = random() % (sizeDLL(q) + 1);
        int j = random() % 100;
        insertDLL(q,x,newINTEGER(j));
        }
    /* now a bunch of unions */
    printf("starting 1000000 unions\n");
    for (i = 0; i < 1000000; ++i)
        {
        unionDLL(q,p);
        unionDLL(p,q);
        }
    /* do some more inserts */
    for (i = 0; i < 25; ++i)
        {
        int x = random() % (sizeDLL(q) + 1);
        int j = random() % 100;
        insertDLL(q,x,newINTEGER(j));
        }
    if (sizeDLL(p) < 100)
        {
        printf("p: ");
        displayDLL(p,stdout);
        printf("\n");
        printf("p (debug): ");
        displayDLLdebug(p,stdout);
        printf("\n");
        printf("\n");
        }
    if (sizeDLL(q) < 100)
        {
        printf("q: ");
        displayDLL(q,stdout);
        printf("\n");
        printf("q (debug): ");
        displayDLLdebug(q,stdout);
        printf("\n");
        printf("\n");
        }
    printf("size of p is %d\n",sizeDLL(p));
    printf("size of q is %d\n",sizeDLL(q));
    printf("value at 10 is %d\n",getINTEGER(getDLL(p,10)));
    printf("setting value at 10 to 55\n");
    freeINTEGER(setDLL(p,10,newINTEGER(55)));
    printf("value at 10 now is %d\n",getINTEGER(getDLL(p,10)));
    freeDLL(p);
    freeDLL(q);
    return 0;
    }
