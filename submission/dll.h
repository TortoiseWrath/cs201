#ifndef __DLL_INCLUDED__
#define __DLL_INCLUDED__

#include <stdio.h>

typedef struct dll DLL;

extern DLL *newDLL(void (*d)(void *, FILE *), void (*f)(void *));
extern void *insertDLL(DLL *items, int index, void *value); // returns the node
extern void *removeDLL(DLL *items, int index);
extern void unionDLL(DLL *recipient, DLL *donor);
extern void *getDLL(DLL *items, int index);
extern void *setDLL(DLL *items, int index, void *value);
extern int sizeDLL(DLL *items);
extern void displayDLL(DLL *items, FILE *);
extern void displayDLLdebug(DLL *items, FILE *);
extern void freeDLL(DLL *items);

extern void removeDLLall(DLL *);
	// Sets the head and tail to null, the size to zero.
	// Only freeing of list nodes, not values, is to be done.

extern void *removeDLLnode(DLL *, void *);
	// Removes the given node from the linked list.
	// Returns the value of the removed node.

extern void firstDLL(DLL *);
	// Start a DLL iterator, setting an object variable to point to the head node

extern void lastDLL(DLL *);
	// Start a DLL iterator, setting an object variable to point to the tail node

extern int moreDLL(DLL *);
	// returns true if the current node is not null, false otherwise

extern void nextDLL(DLL *);
	// moves the current node to the next node in th elist

extern void prevDLL(DLL *);
	// moves the current node to the previous node in the list

extern void *currentDLL(DLL *);
	// returns the value at the current node

#endif
