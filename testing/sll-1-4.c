#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(5911);
    SLL *p = newSLL(displayINTEGER,freeINTEGER);
    int i;
    for (i = 0; i < 14; ++i)
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
    printf("value at 13 is %d\n",getINTEGER(getSLL(p,13)));
    printf("setting value at 13 to 77\n");
    freeINTEGER(setSLL(p,13,newINTEGER(77)));
    printf("value at 13 now is %d\n",getINTEGER(getSLL(p,13)));
    freeSLL(p);
    return 0;
    }
