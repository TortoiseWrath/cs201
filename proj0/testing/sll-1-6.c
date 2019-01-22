#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "real.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(1699);
    SLL *p = newSLL(displayREAL,freeREAL);
    int i;
    for (i = 0; i < 38; ++i)
        {
        int j = random() % 100;
        int k = random() % (sizeSLL(p) + 1);
        j += (random() % 100) / 100.0;
        insertSLL(p,k,newREAL(j));
        }
    freeREAL(removeSLL(p,20));
    freeREAL(removeSLL(p,8));
    freeREAL(removeSLL(p,13));
    insertSLL(p,32,newREAL(33.33));
    insertSLL(p,23,newREAL(58.58));
    insertSLL(p,30,newREAL(93.93));
    insertSLL(p,13,newREAL(16.16));
    insertSLL(p,14,newREAL(62.62));
    insertSLL(p,3,newREAL(59.59));
    freeREAL(removeSLL(p,0));
    freeREAL(removeSLL(p,24));
    freeREAL(removeSLL(p,37));
    freeREAL(removeSLL(p,21));
    freeREAL(removeSLL(p,31));
    insertSLL(p,20,newREAL(26.26));
    insertSLL(p,23,newREAL(12.12));
    insertSLL(p,8,newREAL(70.70));
    freeREAL(removeSLL(p,8));
    insertSLL(p,33,newREAL(25.25));
    insertSLL(p,37,newREAL(39.39));
    freeREAL(removeSLL(p,9));
    freeREAL(removeSLL(p,29));
    freeREAL(removeSLL(p,23));
    insertSLL(p,37,newREAL(23.23));
    freeREAL(removeSLL(p,20));
    insertSLL(p,11,newREAL(81.81));
    insertSLL(p,29,newREAL(8.8));
    insertSLL(p,31,newREAL(20.20));
    insertSLL(p,7,newREAL(90.90));
    freeREAL(removeSLL(p,20));
    insertSLL(p,5,newREAL(85.85));
    freeREAL(removeSLL(p,27));
    insertSLL(p,21,newREAL(50.50));
    freeREAL(removeSLL(p,29));
    freeREAL(removeSLL(p,19));
    insertSLL(p,24,newREAL(94.94));
    insertSLL(p,29,newREAL(78.78));
    freeREAL(removeSLL(p,37));
    if (sizeSLL(p) < 100)
        {
        displaySLL(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeSLL(p));
    printf("value at 4 is %.2lf\n",getREAL(getSLL(p,4)));
    printf("setting value at 4 to 73.10\n");
    freeREAL(setSLL(p,4,newREAL(73.10)));
    printf("value at 4 now is %.2lf\n",getREAL(getSLL(p,4)));
    freeSLL(p);
    return 0;
    }
