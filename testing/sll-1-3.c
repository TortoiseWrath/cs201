#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(5564);
    SLL *p = newSLL(displayINTEGER,freeINTEGER);
    int i;
    for (i = 0; i < 18; ++i)
        {
        int j = random() % 100;
        insertSLL(p,0,newINTEGER(j));
        }
    if (sizeSLL(p) < 100)
        {
        displaySLL(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeSLL(p));
    printf("value at 3 is %d\n",getINTEGER(getSLL(p,3)));
    printf("setting value at 3 to 34\n");
    freeINTEGER(setSLL(p,3,newINTEGER(34)));
    printf("value at 3 now is %d\n",getINTEGER(getSLL(p,3)));
    freeSLL(p);
    return 0;
    }
