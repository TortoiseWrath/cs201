#include "heap.h"

/*
static void (*reader)(FILE *,HEAP *);
static int (*compare)(void *,void *);
static void (*display)(void *,FILE *);
static void (*release)(void *);

...
if (Sorting == REALS)
    {
    reader = readReals;
    release = freeREAL;
    display = displayREAL;
    compare = Order == INCREASING? compareREAL : rcompareREAL;
    }
else if (Sorting == STRINGS)
    {
    reader = readStringsAndTokens;
    release = freeSTRING;
    display = displaySTRING;
    compare = Order == INCREASING? compareSTRING : rcompareSTRING;
    }
else
    {
    reader = readIntegerss;
    release = freeINTEGER;
    display = displayINTEGER;
    compare = Order == INCREASING? compareINTEGER : rcompareINTEGER;
    }

HEAP *h = newHEAP(display,compare,release);
reader(fp,h);

//at this point, the heap is ready for buildHEAP
*/
