#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "sll.h"
#include "real.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(7750);
    QUEUE *p = newQUEUE(displayREAL,freeREAL);
    enqueue(p,newREAL(3.3));
    enqueue(p,newREAL(4.4));
    enqueue(p,newREAL(2.2));
    displayQUEUE(p,stdout);
    printf("\n");
    void *value = dequeue(p);
    displayREAL(value,stdout);
    printf("\n");
    freeREAL(value);
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    value = dequeue(p);
    displayREAL(value,stdout);
    printf("\n");
    freeREAL(value);
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    freeREAL(dequeue(p));
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    freeQUEUE(p);
    return 0;
    }
