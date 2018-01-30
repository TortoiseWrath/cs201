#ifndef __DLL_INCLUDED__
#define __DLL_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll-node.h"

// These signatures taken from the assignment.
// Modified for conventions consistent with remainder of code.

typedef struct dll DLL;

extern DLL *newDLL(void (*d)(void *, FILE *), void (*f)(void *));
extern void insertDLL(DLL *items, int index, void *value);
extern void *removeDLL(DLL *items, int index);
extern void unionDLL(DLL *recipient, DLL *donor);
extern void *getDLL(DLL *items, int index);
extern void *setDLL(DLL *items, int index, void *value);
extern int sizeDLL(DLL *items);
extern void displayDLL(DLL *items, FILE *);
extern void displayDLLbrackets(DLL *items, FILE *, char *open, char *close);
extern void displayDLLdebug(DLL *items, FILE *);
extern void freeDLL(DLL *items);

#endif
