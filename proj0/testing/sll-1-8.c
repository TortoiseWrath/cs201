#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

extern void srandom(unsigned int);
extern long int random(void);

void disp(void *i,FILE *fp) { fprintf(fp,"%d",*(int *)i); }

int values[] = { 1, 2, 3, 4, 5 };

int
main(void)
    {
    srandom(1008);
    SLL *p = newSLL(disp,0);
    unsigned int i;
    /* inserting pointers to int, not INTEGERS */
    for (i = 0; i < sizeof(values)/sizeof(int); ++i)
        insertSLL(p,0,values+i);
    displaySLL(p,stdout);
    printf("\n");
    freeSLL(p);
    return 0;
    }
