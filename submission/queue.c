#include "queue.h"

struct queue {
	DLL *l;
};

// d is the display function
// f is the freeing function
QUEUE *newQUEUE(void (*d)(void *, FILE *), void (*f)(void *)) {
	QUEUE *items = malloc(sizeof(QUEUE));
	assert(items != NULL);
	items->l = newDLL(d, f); // queue consists of a doubly linked list
	return items;
}

void enqueue(QUEUE *items, void *value) {
	insertDLL(items->l, sizeDLL(items->l), value); // insert at tail
	return;
}

// Returns a pointer to the value of the removed item.
void *dequeue(QUEUE *items) {
	assert(sizeQUEUE(items) > 0);
	return removeDLL(items->l, 0); // remove the head
}

// Returns a pointer to the value of the item ready to come off the stack.
void *peekQUEUE(QUEUE *items) {
	assert(sizeQUEUE(items) > 0);
	return getDLL(items->l, 0); // peek at the head
}

int sizeQUEUE(QUEUE *items) {
	return sizeDLL(items->l);
}

// Outputs in the format: <5,6,2,9,1>
void displayQUEUE(QUEUE *items, FILE *fp) {
	displayDLLbrackets(items->l, fp, "<", ">");
	return;
}

// Outputs in the format: head->{{5,6,2,9,1}},tail->{{1,9,2,6,5}}
// (DLL debug)
void displayQUEUEdebug(QUEUE *items, FILE *fp) {
	displayDLLdebug(items->l, fp);
	return;
}

void freeQUEUE(QUEUE *items) {
	freeDLL(items->l);
	free(items);
}
