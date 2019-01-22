#include "stack.h"
#include <stdlib.h>
#include <assert.h>
#include "dll.h"

struct stack {
	DLL *l;
	void (*display)(void *, FILE *);
};

// d is the display function
// f is the freeing function
STACK *newSTACK(void (*d)(void *, FILE *), void (*f)(void *)) {
	STACK *items = malloc(sizeof(STACK));
	assert(items != NULL);
	items->l = newDLL(d, f); // stack consists of a doubly linked list
	items->display = d; // for use by displaySTACK
	return items;
}

void push(STACK *items, void *value) {
	insertDLL(items->l, 0, value); // put the thing at the front of the list
	return;
}

// Returns a pointer to the value of the removed item.
void *pop(STACK *items) {
	return removeDLL(items->l, 0); // remove the head
}

/* Assignment uses both void *pop(STACK *) and void *removeSTACK(stack *)
   so I am adding this as well */
void *removeSTACK(STACK *items) {
	assert(sizeSTACK(items) > 0);
	return pop(items);
}

// Returns a pointer to the value of the item ready to come off the stack.
void *peekSTACK(STACK *items) {
	assert(sizeSTACK(items) > 0);
	return getDLL(items->l, 0); // peek at the head
}

int sizeSTACK(STACK *items) {
	return sizeDLL(items->l);
}

// Outputs in the format: |1,9,2,6,5|
void displaySTACK(STACK *items, FILE *fp) {
	fputc('|', fp);

	int i;
	for (i = 0; i < sizeDLL(items->l); i++) {
		if(i) { // Before all but the first
			fputc(',', fp);
		}
		(items->display)(getDLL(items->l, i), fp);
	}

	fputc('|', fp);
}

// Outputs in the format: head->{1,9,2,6,5},tail->{5}
// (SLL debug)
void displaySTACKdebug(STACK *items, FILE *fp) {
	displayDLLdebug(items->l, fp);
	return;
}

void freeSTACK(STACK *items) {
	freeDLL(items->l);
	free(items);
}
