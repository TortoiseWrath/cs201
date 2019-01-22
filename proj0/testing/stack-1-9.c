#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "dll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(9551);
    STACK *p = newSTACK(displayINTEGER,freeINTEGER);
    int i;
    int j;
    for (j = 0; j < 5; ++j)
        {
        for (i = 0; i < 750000; ++i)
            {
            int j = random() % 100;
            push(p,newINTEGER(j));
            }
        if (sizeSTACK(p) < 100)
            {
            displaySTACK(p,stdout);
            printf("\n");
            displaySTACKdebug(p,stdout);
            printf("\n");
            }
        for (i = 0; i < 375000; ++i)
            {
            freeINTEGER(pop(p));
            }
        if (sizeSTACK(p) < 100)
            {
            displaySTACK(p,stdout);
            printf("\n");
            displaySTACKdebug(p,stdout);
            printf("\n");
            }
        while (sizeSTACK(p) != 0)
            {
            freeINTEGER(pop(p));
            }
        if (sizeSTACK(p) < 100)
            {
            displaySTACK(p,stdout);
            printf("\n");
            displaySTACKdebug(p,stdout);
            printf("\n");
            }
        }
    printf("size is %d\n",sizeSTACK(p));
    freeSTACK(p);
    return 0;
    }
