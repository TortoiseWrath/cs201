#include "sll-node.h"

struct sllnode {
	void *value;
	void *next;
};

SLL_NODE *newSLL_NODE(void *value, SLL_NODE *next) {
	SLL_NODE *n = malloc(sizeof(SLL_NODE));
	assert(n != NULL); // The memory allocated shall not be null.
	n->value = value;
	n->next = next;
	return n;
}

void *getSLL_NODEvalue(SLL_NODE *n) {
	assert(n->value != NULL);
	return n->value;
}

SLL_NODE *getSLL_NODEnext(SLL_NODE *n) {
	return n->next;
}

void setSLL_NODEvalue(SLL_NODE *n, void *value) {
	n->value = value;
	return;
}

void setSLL_NODEnext(SLL_NODE *n, SLL_NODE *next) {
	n->next = next;
	return;
}
