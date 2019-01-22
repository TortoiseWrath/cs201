#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

extern void srandom(unsigned int);
extern long int random(void);

void disp(void *i,FILE *fp) { fprintf(fp,"%d",*(int *)i); }

int values[] = { 1, 2, 3, 4, 5 };

int
main(void)
    {
    srandom(1007);
    QUEUE *p = newQUEUE(disp,0);
    unsigned int i;
    /* inserting pointers to int, not INTEGERS */
    for (i = 0; i < sizeof(values)/sizeof(int); ++i)
        enqueue(p,values+i);
    displayQUEUE(p,stdout);
    printf("\n");
    freeQUEUE(p);
    return 0;
    }
