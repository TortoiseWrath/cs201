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
    srandom(5911);
    STACK *p = newSTACK(displayINTEGER,freeINTEGER);
    int i;
    for (i = 0; i < 14; ++i)
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
    printf("size is %d\n",sizeSTACK(p));
    printf("peek value is %d\n",getINTEGER(peekSTACK(p)));
    freeSTACK(p);
    return 0;
    }
