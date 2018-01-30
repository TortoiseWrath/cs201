#include "stack.h"

struct stack {
	SLL *l;
};

// d is the display function
// f is the freeing function
STACK *newSTACK(void (*d)(void *, FILE *), void (*f)(void *)) {
	STACK *items = malloc(sizeof(STACK));
	assert(items != NULL);
	items->l = newSLL(d, f); // stack consists of a singly linked list
	return items;
}

void push(STACK *items, void *value) {
	insertSLL(items->l, 0, value); // put the thing at the front of the list
	return;
}

// Returns a pointer to the value of the removed item.
void *pop(STACK *items) {
	return removeSLL(items->l, 0); // remove the head
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
	return getSLL(items->l, 0); // peek at the head
}

int sizeSTACK(STACK *items) {
	return sizeSLL(items->l);
}

// Outputs in the format: |1,9,2,6,5|
void displaySTACK(STACK *items, FILE *fp) {
	displaySLLbrackets(items->l, fp, '|', '|');
	return;
}

// Outputs in the format: head->{1,9,2,6,5},tail->{5}
// (SLL debug)
void displaySTACKdebug(STACK *items, FILE *fp) {
	displaySLLdebug(items->l, fp);
	return;
}

void freeSTACK(STACK *items) {
	freeSLL(items->l);
	free(items);
}
