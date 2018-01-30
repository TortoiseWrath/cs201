#include "dll-node.h"

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
