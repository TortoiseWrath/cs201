#ifndef __NODE_INCLUDED__
#define __NODE_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// These signatures taken from the assignment.
// Modified for conventions consistent with remainder of code.

typedef struct sllnode SLL_NODE;

extern SLL_NODE *newSLL_NODE(void *value, SLL_NODE *next);
extern void *getSLL_NODEvalue(SLL_NODE *n);
extern SLL_NODE *getSLL_NODEnext(SLL_NODE *n);
extern void setSLL_NODEvalue(SLL_NODE *n, void *value);
extern void setSLL_NODEnext(SLL_NODE *n, SLL_NODE *next);

#endif
