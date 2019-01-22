#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "sll.h"
#include "string.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(3408);
    QUEUE *p = newQUEUE(displaySTRING,freeSTRING);
    enqueue(p,newSTRING("a"));
    enqueue(p,newSTRING("c"));
    enqueue(p,newSTRING("b"));
    displayQUEUE(p,stdout);
    printf("\n");
    void *value = dequeue(p);
    displaySTRING(value,stdout);
    printf("\n");
    freeSTRING(value);
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    value = dequeue(p);
    displaySTRING(value,stdout);
    printf("\n");
    freeSTRING(value);
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    freeSTRING(dequeue(p));
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    freeQUEUE(p);
    return 0;
    }
