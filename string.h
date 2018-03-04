#ifndef __STRING_INCLUDED__
#define __STRING_INCLUDED__

#include <stdio.h>

typedef struct STRING STRING;

extern STRING *newSTRING(char *);
extern int getSTRING(STRING *);
extern int setSTRING(STRING *,char *);
extern int compareSTRING(void *,void *);
extern void displaySTRING(void *,FILE *);
extern void freeSTRING(void *);

#endif
