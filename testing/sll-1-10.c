#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(9551);
    SLL *p = newSLL(displayINTEGER,freeINTEGER);
    int i;
    for (i = 0; i < 1000000; ++i)
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
    printf("value at 812276 is %d\n",getINTEGER(getSLL(p,812276)));
    printf("setting value at 812276 to 84\n");
    freeINTEGER(setSLL(p,812276,newINTEGER(84)));
    printf("value at 812276 now is %d\n",getINTEGER(getSLL(p,812276)));
    freeSLL(p);
    return 0;
    }
