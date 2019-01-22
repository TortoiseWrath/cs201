#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "sll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(8083);
    QUEUE *p = newQUEUE(displayINTEGER,freeINTEGER);
    int i;
    for (i = 0; i < 1000000; ++i)
        {
        int j = random() % 100;
        enqueue(p,newINTEGER(j));
        }
    for (i = 0; i < 1000000; ++i)
        {
        freeINTEGER(dequeue(p));
        }
    if (sizeQUEUE(p) < 100)
        {
        displayQUEUE(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeQUEUE(p));
    freeQUEUE(p);
    return 0;
    }
