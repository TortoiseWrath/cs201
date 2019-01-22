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
    srandom(7684);
    STACK *p = newSTACK(displayINTEGER,freeINTEGER);
    int i;
    for (i = 0; i < 15; ++i)
        {
        int j = random() % 100;
        push(p,newINTEGER(j));
        }
    for (i = 0; i < 15; ++i)
        {
        freeINTEGER(pop(p));
        }
    if (sizeSTACK(p) < 100)
        {
        displaySTACK(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeSTACK(p));
    freeSTACK(p);
    return 0;
    }
