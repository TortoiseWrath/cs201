#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "real.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(3793);
    DLL *p = newDLL(displayREAL,freeREAL);
    int i;
    for (i = 0; i < 10000; ++i)
        {
        int j = random() % 100;
        int k = random() % (sizeDLL(p) + 1);
        j += (random() % 100) / 100.0;
        insertDLL(p,k,newREAL(j));
        }
    if (sizeDLL(p) < 100)
        {
        displayDLL(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeDLL(p));
    printf("value at 1590 is %.2lf\n",getREAL(getDLL(p,1590)));
    printf("setting value at 1590 to 88.37\n");
    freeREAL(setDLL(p,1590,newREAL(88.37)));
    printf("value at 1590 now is %.2lf\n",getREAL(getDLL(p,1590)));
    freeDLL(p);
    return 0;
    }
