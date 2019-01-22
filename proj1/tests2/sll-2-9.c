#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(7115);
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
    freeSLL(p);
    return 0;
    }
