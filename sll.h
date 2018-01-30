#ifndef __SLL_INCLUDED__
#define __SLL_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sll-node.h"

// These signatures taken from the assignment.
// Modified for conventions consistent with remainder of code.

typedef struct sll SLL;

extern SLL *newSLL(void (*d)(void *, FILE *), void (*f)(void *));
extern void insertSLL(SLL *items, int index, void *value);
extern void *removeSLL(SLL *items, int index);
extern void unionSLL(SLL *recipient, SLL *donor);
extern void *getSLL(SLL *items, int index);
extern void *setSLL(SLL *items, int index, void *value);
extern int sizeSLL(SLL *items);
extern void displaySLL(SLL *items, FILE *);
extern void displaySLLbrackets(SLL *items, FILE *, char *open, char *close);
extern void displaySLLdebug(SLL *items, FILE *);
extern void freeSLL(SLL *items);

#endif
