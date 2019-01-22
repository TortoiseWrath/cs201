#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "dll.h"
#include "real.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(7750);
    STACK *p = newSTACK(displayREAL,freeREAL);
    push(p,newREAL(3.3));
    push(p,newREAL(4.4));
    push(p,newREAL(2.2));
    displaySTACK(p,stdout);
    printf("\n");
    void *value = pop(p);
    displayREAL(value,stdout);
    printf("\n");
    freeREAL(value);
    displaySTACK(p,stdout);
    printf("\n");
    displaySTACKdebug(p,stdout);
    printf("\n");
    value = pop(p);
    displayREAL(value,stdout);
    printf("\n");
    freeREAL(value);
    displaySTACK(p,stdout);
    printf("\n");
    displaySTACKdebug(p,stdout);
    printf("\n");
    freeREAL(pop(p));
    displaySTACK(p,stdout);
    printf("\n");
    displaySTACKdebug(p,stdout);
    printf("\n");
    freeSTACK(p);
    return 0;
    }
