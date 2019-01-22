#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "dll.h"
#include "string.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(3408);
    STACK *p = newSTACK(displaySTRING,freeSTRING);
    push(p,newSTRING("a"));
    push(p,newSTRING("c"));
    push(p,newSTRING("b"));
    displaySTACK(p,stdout);
    printf("\n");
    void *value = pop(p);
    displaySTRING(value,stdout);
    printf("\n");
    freeSTRING(value);
    displaySTACK(p,stdout);
    printf("\n");
    displaySTACKdebug(p,stdout);
    printf("\n");
    value = pop(p);
    displaySTRING(value,stdout);
    printf("\n");
    freeSTRING(value);
    displaySTACK(p,stdout);
    printf("\n");
    displaySTACKdebug(p,stdout);
    printf("\n");
    freeSTRING(pop(p));
    displaySTACK(p,stdout);
    printf("\n");
    displaySTACKdebug(p,stdout);
    printf("\n");
    freeSTACK(p);
    return 0;
    }
