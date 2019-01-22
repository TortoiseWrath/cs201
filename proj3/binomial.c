#include "binomial.h"
#include "dll.h"
#include "queue.h"
#include <stdlib.h>
#include <assert.h> // assert
#include <string.h> // memset

static int log2i(int x) {
	assert(x>0);
	return sizeof(int) * 8 - __builtin_clz(x) - 1;
	/* ugly and slightly non-portable but eliminates need to link math library
	   (not sure if -lm would be consistently passed to gcc in testing;
   		I had some issues with that in the test dropboxes)
	   source: https://stackoverflow.com/a/22418446 */
}

typedef struct binomialnode BINOMIAL_NODE;
static BINOMIAL_NODE *newBINOMIAL_NODE(void *value);

struct binomialnode {
	void *key;
	int degree; // number of children
	BINOMIAL_NODE *parent;
	BINOMIAL_NODE *leftmostChild;
	BINOMIAL_NODE *rightmostChild;
	BINOMIAL_NODE *rightSibling;
};

static void consolidate(BINOMIAL *b);
static void updateConsolidationArray(BINOMIAL *b, BINOMIAL_NODE *D[], BINOMIAL_NODE *spot);
static void insertChild(BINOMIAL_NODE *x, BINOMIAL_NODE *y);
static BINOMIAL_NODE *combine(BINOMIAL *b, BINOMIAL_NODE *x, BINOMIAL_NODE *y);
static BINOMIAL_NODE *bubbleUp(BINOMIAL *b, BINOMIAL_NODE *n);


struct binomial {
	DLL *rootList;
	BINOMIAL_NODE *extreme;
	int size;
	void (*display)(void *, FILE *);
	int (*compare)(void *, void *);
	void (*update)(void *, void *);
	void (*release)(void *);
};

BINOMIAL *newBINOMIAL(
    void (*display)(void *, FILE *),
    int (*compare)(void *, void *),
    void (*update)(void *, void *),
    void (*release)(void *)) {
	BINOMIAL *b = malloc(sizeof(BINOMIAL));
	b->display = display;
	b->compare = compare;
	b->update = update;
	b->release = release;
	b->rootList = newDLL(display, release);
	b->size = 0;
	b->extreme = NULL;
	return b;
}

void *insertBINOMIAL(BINOMIAL *b, void *value) {
	BINOMIAL_NODE *node = newBINOMIAL_NODE(value);
	insertDLL(b->rootList, sizeDLL(b->rootList), node);
	b->size++;
	consolidate(b);
	return node;
}

int sizeBINOMIAL(BINOMIAL *b) {
	return b->size;
}

void unionBINOMIAL(BINOMIAL *b, BINOMIAL *donor) {
	unionDLL(b->rootList, donor->rootList);
	b->size += donor->size;
	donor->rootList = newDLL(donor->display, donor->release);
	donor->size = 0;
	donor->extreme = NULL;
	consolidate(b);
}

void deleteBINOMIAL(BINOMIAL *b, void *n) {
	decreaseKeyBINOMIAL(b, n, NULL);
	extractBINOMIAL(b);
}

void decreaseKeyBINOMIAL(BINOMIAL *b, void *node, void *v) {
	BINOMIAL_NODE *n = node;
	n->key = v;
	BINOMIAL_NODE *result = bubbleUp(b, n);
	// also update b's extreme value pointer if necessary
	if(result->parent == result && b->compare(b->extreme->key, result->key) > 0) {
		b->extreme = result;
	}
}

void *peekBINOMIAL(BINOMIAL *b) {
	return b->extreme->key;
}

void *extractBINOMIAL(BINOMIAL *b) {
	BINOMIAL_NODE *y = b->extreme;

	// find y in the root list and remove
	int index = 0;
	firstDLL(b->rootList);
	for(; index < sizeDLL(b->rootList); index++) {
		if(getDLL(b->rootList, index) == y) {
			break;
		}
	}
	removeDLL(b->rootList, index);

	DLL *consolidationList = newDLL(b->display, b->release);
	BINOMIAL_NODE *child = y->leftmostChild;
	while(child != NULL) {
		child->parent = child;
		insertDLL(consolidationList, sizeDLL(consolidationList), child);
		child = child->rightSibling;
	}
	unionDLL(consolidationList, b->rootList);
	freeDLL(b->rootList);
	b->rootList = consolidationList;
	consolidate(b);
	b->size--;
	void *value = y->key;
	free(y);
	return value;
}

void statisticsBINOMIAL(BINOMIAL *b, FILE *fp) {
	fprintf(fp, "size: %i\nrootlist size: %i\n", sizeBINOMIAL(b), sizeDLL(b->rootList));
	if(sizeBINOMIAL(b) > 0) {
		fputs("extreme: ", fp);
		b->display(b->extreme->key, fp);
		fputc('\n', fp);
	}
}

void displayBINOMIAL(BINOMIAL *b, FILE *fp) {
	fputs("rootlist:", fp);
	firstDLL(b->rootList);
	BINOMIAL_NODE *current = NULL;
	int prevDegree = -1;
	while(moreDLL(b->rootList)) {
		fputc(' ', fp);
		current = currentDLL(b->rootList);
		assert(current != NULL);

		// Display NULL for unused trees
		while(prevDegree != current->degree - 1) {
			prevDegree++;
			fputs("NULL ", fp);
		}
		prevDegree = current->degree;

		b->display(current->key, fp);
		if(b->extreme == current) {
			fputc('*', fp);
		}
		// This line can print the degree of the node for debugging purposes.
		// fprintf(fp,"[%i]",current->degree);
		nextDLL(b->rootList);
	}
	fputc('\n', fp);
}

void displayBINOMIALdebug(BINOMIAL *b, FILE *fp) {

	if(sizeDLL(b->rootList) == 0) {
		fputs("{{}}\n", fp);
		return;
	}

	// These queues will contain pointers to BINOMIAL_NODEs
	QUEUE *currentLevel = newQUEUE(NULL, NULL);
	QUEUE *nextLevel = newQUEUE(NULL, NULL);

	// Enqueue all root nodes
	firstDLL(b->rootList);
	while(moreDLL(b->rootList)) {
		enqueue(currentLevel, currentDLL(b->rootList));
		nextDLL(b->rootList);
	}

	BINOMIAL_NODE *current = NULL;
	BINOMIAL_NODE *child = NULL;
	int beginningOfLevel = 1;
	while(sizeQUEUE(currentLevel) > 0) {
		current = dequeue(currentLevel);

		// Determine whether this node is the beginning of a level
		if(beginningOfLevel) {
			fputs("{{", fp);
			beginningOfLevel = 0;
		}

		// Display node
		b->display(current->key, fp);

		// Enqueue children of node
		child = current->leftmostChild;
		while(child != NULL) {
			enqueue(nextLevel, child);
			child = child->rightSibling;
		}

		// Determine whether this node is the end of the level
		if(sizeQUEUE(currentLevel) == 0) {
			freeQUEUE(currentLevel);
			currentLevel = nextLevel;
			nextLevel = newQUEUE(NULL, NULL);
			fputs("}}\n", fp);
			beginningOfLevel = 1;
		}

		// Determine whether this node is the end of the level of a subtree
		else if(current->parent != current && current->rightSibling == NULL) {
			fputs("}}{{", fp);
		}

		else {
			fputc(',', fp);
		}
	}

	freeQUEUE(currentLevel);
	freeQUEUE(nextLevel);
}

void freeBINOMIAL(BINOMIAL *b) {
	while(sizeBINOMIAL(b) > 0) {
		void *extracted = extractBINOMIAL(b);
		b->release(extracted);
	}
	freeDLL(b->rootList);
	free(b);
}


// Helper functions based on Dr. Lusth's pseudocode

static void consolidate(BINOMIAL *b) {
	// create the consolidation array
	int consolidationArraySize = log2i(b->size) + 1;
	BINOMIAL_NODE *D[consolidationArraySize];
	memset(D, 0, sizeof(D));

	// place all the subheaps in the D array, combining as necessary
	while(sizeDLL(b->rootList) > 0) {
		BINOMIAL_NODE *spot = getDLL(b->rootList, 0);
		removeDLL(b->rootList, 0);
		updateConsolidationArray(b, D, spot);
	}

	// transfer the D array back to the heap, keeping track of the extreme value
	b->extreme = NULL;
	for(int i = 0; i < consolidationArraySize; i++) {
		if(D[i] != NULL) {
			insertDLL(b->rootList, sizeDLL(b->rootList), D[i]);
			assert(D[i]->parent == D[i]);
			if(b->extreme == NULL || b->compare(b->extreme->key, D[i]->key) > 0) {
				// If there is currently no extreme value or D[i] is more extreme
				b->extreme = D[i];
			}
		}
	}

}

static void updateConsolidationArray(BINOMIAL *b, BINOMIAL_NODE *D[], BINOMIAL_NODE *spot) {
	int degree = spot->degree;
	while(D[degree] != NULL) {
		spot = combine(b, spot, D[degree]);
		D[degree] = NULL;
		degree++;
	}
	D[degree] = spot;
}

static BINOMIAL_NODE *combine(BINOMIAL *b, BINOMIAL_NODE *x, BINOMIAL_NODE *y) {
	if(b->compare(x->key, y->key) < 0) {
		// b's comparator says x's value is more extreme than y's
		insertChild(x, y);
		return x;
	}
	else {
		insertChild(y, x);
		return y;
	}
}

// inserts y into the children of x
static void insertChild(BINOMIAL_NODE *x, BINOMIAL_NODE *y) {
	if(x->degree == 0) {
		x->leftmostChild = y;
		x->rightmostChild = y;
		y->parent = x;
	}
	else {
		x->rightmostChild->rightSibling = y;
		x->rightmostChild = y;
		y->parent = x;
	}
	x->degree++;
	y->rightSibling = NULL;
}

static BINOMIAL_NODE *bubbleUp(BINOMIAL *b, BINOMIAL_NODE *n) {
	BINOMIAL_NODE *p = n->parent;

	if(n == p) {
		// n is the root of a subheap
		return n;
	}
	if(b->compare(n->key, p->key) >= 0) {
		// b's comparator says n's value isn't smaller than its parent's
		return n;
	}
	if(b->update != NULL) {
		b->update(n->key, p);
		b->update(p->key, n);
	}
	void *temp = n->key;
	n->key = p->key;
	p->key = temp;
	return bubbleUp(b, p);
}


// Helper functions for storage of nodes

static BINOMIAL_NODE *newBINOMIAL_NODE(void *key) {
	BINOMIAL_NODE *n = malloc(sizeof(BINOMIAL_NODE));
	n->key = key;
	n->degree = 0;
	n->parent = n;
	n->leftmostChild = NULL;
	n->rightmostChild = NULL;
	n->rightSibling = NULL;
	return n;
}
