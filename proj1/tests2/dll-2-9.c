#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(363);
    DLL *p = newDLL(displayINTEGER,freeINTEGER);
    int i;
    for (i = 0; i < 1000000; ++i)
        {
        int j = random() % 100;
        insertDLL(p,0,newINTEGER(j));
        }
    if (sizeDLL(p) < 100)
        {
        displayDLL(p,stdout);
        printf("\n");
        }
    if (sizeDLL(p) > 0)
        {
        i = random() % sizeDLL(p);
        int value = random() % 100;
        printf("size is %d\n",sizeDLL(p));
        printf("value at %d is %d\n",i,getINTEGER(getDLL(p,i)));
        printf("setting value at %d to %d\n",i,value);
        freeINTEGER(setDLL(p,i,newINTEGER(value)));
        printf("value at %d now is %d\n",i,getINTEGER(getDLL(p,i)));
        }
    freeDLL(p);
    return 0;
    }
