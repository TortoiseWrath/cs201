#include "dll.h"
#include <stdlib.h>
#include <assert.h>

typedef struct dllnode DLL_NODE;

// Storage of nodes

extern DLL_NODE *newDLL_NODE(void *value, DLL_NODE *next, DLL_NODE *prev);
extern void *getDLL_NODEvalue(DLL_NODE *n);
extern DLL_NODE *getDLL_NODEnext(DLL_NODE *n);
extern DLL_NODE *getDLL_NODEprev(DLL_NODE *n);
extern void setDLL_NODEvalue(DLL_NODE *n, void *value);
extern void setDLL_NODEnext(DLL_NODE *n, DLL_NODE *next);
extern void setDLL_NODEprev(DLL_NODE *n, DLL_NODE *prev);

// Local function to get a node (not a value) from the list

static DLL_NODE *getNodeDLL(DLL *items, int index);

struct dll {
	DLL_NODE *head;
	DLL_NODE *tail;
	int size;
	void (*display)(void *, FILE *);
	void (*free)(void *);
};

// newDLL implementation taken from the assignment.
// Modified for conventions consistent with remainder of code.
// d is the display function
// f is the freeing function
DLL *newDLL(void (*d)(void *, FILE *), void (*f)(void *)) {
	DLL *items = malloc(sizeof(DLL));
	assert(items != NULL); // The memory allocated shall not be null.
	items->head = NULL;
	items->tail = NULL;
	items->size = 0;
	items->display = d;
	items->free = f;
	return items;
}


// Runs in constant time for insertions at a constant distance from the front.
// Runs in constant time for insertions at a constant distance from the back.
void insertDLL(DLL *items, int index, void *value) {
	assert(index >= 0);
	assert(index <= items->size);

	DLL_NODE *n = newDLL_NODE(value, NULL, NULL);

	// Insert only item?
	if(items->size == 0) {
		items->head = n;
		items->tail = n;
	}

	// Insert at the very back of the list?
	else if(index == items->size) {
		setDLL_NODEprev(n, items->tail);
		setDLL_NODEnext(items->tail, n);
		items->tail = n;
	}

	// Insert somewhere else?
	else {
		DLL_NODE *cur = getNodeDLL(items, index);
		DLL_NODE *prev = getDLL_NODEprev(cur);

		// Before: prev cur
		// After: prev n cur

		if(prev == NULL) { // very front of list
			items->head = n;
		}
		else {
			setDLL_NODEnext(prev, n);
		}
		setDLL_NODEprev(n, prev);
		setDLL_NODEnext(n, cur);
		setDLL_NODEprev(cur, n);
	}

	items->size++;
	return;

}

// Returns a pointer to the value of the removed node.
// Runs in constant time for removals at a constant distance from the front.
// Runs in constant time for removals at a constant distance from the back.
void *removeDLL(DLL *items, int index) {
	assert(items->size >= 0);
	assert(index >= 0);
	assert(index < items->size);

	DLL_NODE *cur = getNodeDLL(items, index);
	DLL_NODE *prev = getDLL_NODEprev(cur);
	DLL_NODE *next = getDLL_NODEnext(cur);

	// Before: prev cur next
	// After: prev next
	if(prev == NULL) { // If head was removed
		items->head = next;
	}
	else {
		setDLL_NODEnext(prev, next);
	}
	if(next == NULL) { // If tail was removed
		items->tail = prev;
	}
	else {
		setDLL_NODEprev(next, prev);
	}

	items->size--;

	void *val = getDLL_NODEvalue(cur);
	free(cur); //free the node
	return val;
}

// Moves all items in the donor list to the end of the recipient list.
// Runs in constant time.
// Does not check whether any nodes are identical between the two lists.
// If two nodes are identical (same address) there will be problems.
void unionDLL(DLL *recipient, DLL *donor) {
	if(donor->size == 0) {
		return; // do nothing
	}
	if(recipient->size == 0) {
		recipient->head = donor->head;
	}
	else {
		setDLL_NODEnext(recipient->tail, donor->head); // Transplant the head.
		setDLL_NODEprev(donor->head, recipient->tail);
	}
	recipient->tail = donor->tail;
	recipient->size += donor->size;

	// Clear the donor.
	donor->head = NULL;
	donor->tail = NULL;
	donor->size = 0;

	return;
}

// Returns a pointer to the value of the node at the given index.
// Runs in constant time for retrievals at a constant distance from the front.
// Runs in constant time for retrievals at a constant distance from the back.
void *getDLL(DLL *items, int index) {
	assert(index >= 0);
	assert(index < items->size);

	DLL_NODE *n = getNodeDLL(items, index);
	return getDLL_NODEvalue(n);
}


// Returns a pointer to the value of the former node at the given index.
// If index == size, value is appended to the list and null pointer is returned.
// Runs in constant time for updates at a constant distance from the front.
// Runs in constant time for updates at a constant distance from the back.
void *setDLL(DLL *items, int index, void *value) {
	assert(index >= 0);
	assert(index <= items->size);

	if(index == items->size) {
		insertDLL(items, items->size, value);
		return NULL;
	}

	DLL_NODE *n = getNodeDLL(items, index);
	void *oldval = getDLL_NODEvalue(n);
	setDLL_NODEvalue(n, value);
	return oldval;
}


int sizeDLL(DLL *items) {
	return items->size;
}


// Outputs in the format: {{5, 6, 2, 9, 1}}
void displayDLL(DLL *items, FILE *fp) {
	assert(items->display != NULL);
	fputs("{{", fp);

	DLL_NODE *n = items->head; // Start at the head
	if(n != NULL) { // Skip if there is no head (empty)
		int ishead = 1;
		do {
			if(!ishead) { // Put commas before non-head values
				fputc(',', fp);
			}
			ishead = 0; // All values after head will be non-head
			(items->display)(getDLL_NODEvalue(n), fp);
		}
		while((n = getDLL_NODEnext(n)));
	}

	fputs("}}", fp);
	return;
}

// Outputs in the format: head->{{5,6,2,9,1}},tail->{{1}}
void displayDLLdebug(DLL *items, FILE *fp) {
	assert(items->display != NULL);

	fputs("head->", fp);
	displayDLL(items, fp);

	fputs(",tail->{{", fp);
	DLL_NODE *n = items->tail;
	if(n != NULL) { // Skip if there is no tail (empty)
		/* // Uncomment to display elements backwards from tail
		int istail = 1;
		do {
			if(!istail) { // Put commas before non-tail values
				fputc(',', fp);
			}
			istail = 0; // All values before tail will be non-tail
			(items->display)(getDLL_NODEvalue(n), fp);
		}
		while((n = getDLL_NODEprev(n)));
		*/
		(items->display)(getDLL_NODEvalue(n), fp);
	}

	fputs("}}", fp);
	return;
}

// Frees the values using the freeing function of the list.
// Frees the nodes.
// Frees the DLL.
/* This only frees about 60% of the memory but I haven't figured out why yet. */
void freeDLL(DLL *items) {
	DLL_NODE *n2 = items->head; // Start at the head
	DLL_NODE *n;
	while((n = n2)) {
		if(items->free != NULL) {
			(items->free)(getDLL_NODEvalue(n)); // free the value
		}
		n2 = getDLL_NODEnext(n); // Save a pointer to the next node
		free(n); // Free the node
	}

	free(items); // Free the DLL

	return;
}



// Local function to get a node (not a value) from the list

// Returns a pointer to the node at the given index.
// Runs in constant time for nodes at a constant distance from the front.
// Runs in constant time for nodes at a constant distance from the back.
static DLL_NODE *getNodeDLL(DLL *items, int index) {
	assert(index >= 0);
	assert(index < items->size);

	DLL_NODE *n = NULL;

	// Closer to the back of the list?
	// 0 1 2 3 4 (size 5): > 2
	// 0 1 2 3 4 5 (size 6): > 3
	if(index > items->size / 2) {
		n = items->tail;
		int cur;
		for(cur = items->size - 1; cur > index; cur--) {
			n = getDLL_NODEprev(n);
		}
	}

	else { // Closer to the front of the list
		n = items->head;
		int cur;
		for(cur = 0; cur < index; cur++) {
			n = getDLL_NODEnext(n);
		}
	}

	assert(n != NULL);
	return n;
}



// Storage of nodes

struct dllnode {
	void *value;
	DLL_NODE *next;
	DLL_NODE *prev;
};

DLL_NODE *newDLL_NODE(void *value, DLL_NODE *next, DLL_NODE *prev) {
	DLL_NODE *n = malloc(sizeof(DLL_NODE));
	assert(n != NULL); // The memory allocated shall not be null.
	n->value = value;
	n->next = next;
	n->prev = prev;
	return n;
}

void *getDLL_NODEvalue(DLL_NODE *n) {
	assert(n->value != NULL);
	return n->value;
}

DLL_NODE *getDLL_NODEnext(DLL_NODE *n) {
	return n->next;
}

DLL_NODE *getDLL_NODEprev(DLL_NODE *n) {
	return n->prev;
}

void setDLL_NODEvalue(DLL_NODE *n, void *value) {
	n->value = value;
	return;
}

void setDLL_NODEnext(DLL_NODE *n, DLL_NODE *next) {
	n->next = next;
	return;
}

void setDLL_NODEprev(DLL_NODE *n, DLL_NODE *prev) {
	n->prev = prev;
	return;
}
