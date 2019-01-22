#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "real.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(6566);
    SLL *p = newSLL(displayREAL,freeREAL);
    int i;
    for (i = 0; i < 10000; ++i)
        {
        int j = random() % 100;
        int k = random() % (sizeSLL(p) + 1);
        j += (random() % 100) / 100.0;
        insertSLL(p,k,newREAL(j));
        }
    if (sizeSLL(p) < 100)
        {
        displaySLL(p,stdout);
        printf("\n");
        }
    if (sizeSLL(p) > 0)
        {
        i = random() % sizeSLL(p);
        double value = (random() % 100) / 10.0;
        printf("size is %d\n",sizeSLL(p));
        printf("value at %d is %lf\n",i,getREAL(getSLL(p,i)));
        printf("setting value at %d to %lf\n",i,value);
        freeREAL(setSLL(p,i,newREAL(value)));
        printf("value at %d now is %lf\n",i,getREAL(getSLL(p,i)));
        }
    freeSLL(p);
    return 0;
    }
