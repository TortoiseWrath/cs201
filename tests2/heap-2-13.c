#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "stack.h"
#include "queue.h"
#include "heap.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(2014);
    //INTEGER test of HEAP
    int i;
    HEAP *p = newHEAP(displayINTEGER,rcompareINTEGER,freeINTEGER);
    for (i = 0; i < 107263; ++i)
        {
        int j = random();
        INTEGER *a = newINTEGER(j);
        insertHEAP(p,a);
        }
    buildHEAP(p);
    printf("peek: %d\n",getINTEGER(peekHEAP(p)));
    //if (sizeHEAP(p) < 200)
    //    {
    //    printf("heap: ");
    //    displayHEAP(p,stdout);
    //    printf("\n");
    //    printf("debug:\n");
    //    displayHEAPdebug(p,stdout);
    //    }
    printf("size is %d\n",sizeHEAP(p));
    for (i = 0; i < 107253; ++i)
        {
        INTEGER *x = extractHEAP(p);
        if (sizeHEAP(p) < 20)
            printf("extracted %d\n",getINTEGER(x));
        freeINTEGER(x);
        }
    printf("peek: %d\n",getINTEGER(peekHEAP(p)));
    //if (sizeHEAP(p) < 200)
    //    {
    //    printf("heap: ");
    //    displayHEAP(p,stdout);
    //    printf("\n");
    //    printf("debug:\n");
    //    displayHEAPdebug(p,stdout);
    //    }
    printf("size is %d\n",sizeHEAP(p));
    freeHEAP(p);
    return 0;
    }
