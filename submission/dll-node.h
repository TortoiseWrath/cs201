#ifndef __DLL_NODE_INCLUDED__
#define __DLL_NODE_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct dllnode DLL_NODE;

extern DLL_NODE *newDLL_NODE(void *value, DLL_NODE *next, DLL_NODE *prev);
extern void *getDLL_NODEvalue(DLL_NODE *n);
extern DLL_NODE *getDLL_NODEnext(DLL_NODE *n);
extern DLL_NODE *getDLL_NODEprev(DLL_NODE *n);
extern void setDLL_NODEvalue(DLL_NODE *n, void *value);
extern void setDLL_NODEnext(DLL_NODE *n, DLL_NODE *next);
extern void setDLL_NODEprev(DLL_NODE *n, DLL_NODE *prev);

#endif
