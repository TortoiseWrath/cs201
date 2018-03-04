#ifndef __REAL_INCLUDED__
#define __REAL_INCLUDED__

#include <stdio.h>

typedef struct REAL REAL;

extern REAL *newREAL(double);
extern int getREAL(REAL *);
extern int setREAL(REAL *,double);
extern int compareREAL(void *,void *);
extern void displayREAL(void *,FILE *);
extern void freeREAL(void *);

#endif
