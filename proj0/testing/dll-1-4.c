#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(7684);
    DLL *p = newDLL(displayINTEGER,freeINTEGER);
    int i;
    for (i = 0; i < 15; ++i)
        {
        int j = random() % 100;
        insertDLL(p,0,newINTEGER(j));
        }
    if (sizeDLL(p) < 100)
        {
        displayDLL(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeDLL(p));
    printf("value at 13 is %d\n",getINTEGER(getDLL(p,13)));
    printf("setting value at 13 to 58\n");
    freeINTEGER(setDLL(p,13,newINTEGER(58)));
    printf("value at 13 now is %d\n",getINTEGER(getDLL(p,13)));
    freeDLL(p);
    return 0;
    }
