#include "heap.h"
#include "bst.h"
#include "stack.h"
#include "queue.h"
#include <stdlib.h>
#include <assert.h>

struct heap {
	BST *tree;
	void (*display)(void *, FILE *);
	int (*compare)(void *, void *);
	void (*f)(void *);
	STACK *nodestack;
};

static void heapify(HEAP *h, BSTNODE *i);
static STACK *bftraverse(HEAP *h);

HEAP *newHEAP(
    void (*d)(void *,FILE *),    //display
    int (*c)(void *,void *),     //compare
    void (*f)(void *)          //free
) {
	HEAP *h = malloc(sizeof(HEAP));
	assert(h != NULL);
	h->tree = newBST(d, c, NULL, f); //use generic swapper
	h->display = d;
	h->compare = c;
	h->f = f;
	h->nodestack = newSTACK(d, NULL); //stack to help find leaves and such
	return h;
}

//insert without heapifying
void insertHEAP(HEAP *h, void *value) {
	BSTNODE *node = newBSTNODE(value);
	// printf("parent is %p\n", getBSTNODEparent(node));
	setBSTNODEparent(node, NULL);
	setBSTNODEleft(node, NULL);
	setBSTNODEright(node, NULL);
	/* assert(getBSTNODEparent(node) == NULL);
	assert(getBSTNODEleft(node) == NULL);
	assert(getBSTNODEright(node) == NULL); */
	BST *t = h->tree;
	// printf("tree has size %i\n",sizeBST(t));
	if(sizeBST(t) == 0) {
		// Create the root
		setBSTroot(t, node);
		// printf("created root %p\n", node);
	}
	else {
		BSTNODE *last = peekSTACK(h->nodestack);
		assert(last != NULL);
		// printf("last node is %p\n",last);

		if(getBSTNODEparent(last) != NULL && getBSTNODEleft(getBSTNODEparent(last)) == last) {
			// printf("last node is a left child of %p\n",getBSTNODEparent(last));
			// Last node is a left child
			last = getBSTNODEparent(last);
			// printf("%p is the right child of %p now\n",node,last);
			setBSTNODEparent(node, last);
			setBSTNODEright(last, node);
		}
		else {
			while(getBSTNODEparent(last) != NULL && getBSTNODEright(getBSTNODEparent(last)) == last) {
				// Go up until not right child
				// printf("%p is a right child\n",last);
				last = getBSTNODEparent(last);
			}
			// printf("%p is not a right child\n",last);
			if(getBSTNODEparent(last) != NULL) {
				// Did not reach root: go to right sibling
				// printf("%p has sibling %p\n",last,getBSTNODEright(getBSTNODEparent(last)));
				last = getBSTNODEright(getBSTNODEparent(last));
				assert(last != NULL); // right sibling must exist
			}
			while(getBSTNODEleft(last) != NULL) {
				// Go down left side
				// printf("%p is on the left of %p\n",getBSTNODEleft(last),last);
				last = getBSTNODEleft(last);
			}
			// printf("%p is the left child of %p now\n",node,last);
			setBSTNODEparent(node, last);
			setBSTNODEleft(last, node);
		}
	}

	setBSTsize(t, sizeBST(t) + 1);
	push(h->nodestack, node);
}

// builds a min-heap
void buildHEAP(HEAP *h) {
	// Algorithm: Cormen et al. 157
	assert(h->nodestack != NULL);
	if(sizeHEAP(h) == 1) { // nothing to do
		return;
	}

	while(getBSTNODEleft(peekSTACK(h->nodestack)) == NULL) { // pop the leaves
		pop(h->nodestack);
	}
	while(sizeSTACK(h->nodestack) > 0) {
		heapify(h, pop(h->nodestack));
	}

	freeSTACK(h->nodestack); // note stack has null free function for values so values are unaffected
	h->nodestack = bftraverse(h); // rebuild the stack with a breadth-first traversal for use by extractHEAP
	return;
}

static void heapify(HEAP *h, BSTNODE *i) {
	// Algorithm: Cormen et al. 154
	if(i == NULL) return;
	BSTNODE *l = getBSTNODEleft(i);
	BSTNODE *r = getBSTNODEright(i);
	BSTNODE *largest;
	if(l != NULL && h->compare(getBSTNODEvalue(l), getBSTNODEvalue(i)) < 0) {
		largest = l;
	}
	else {
		largest = i;
	}
	if(r != NULL && h->compare(getBSTNODEvalue(r), getBSTNODEvalue(largest)) < 0) {
		largest = r;
	}
	if(largest != i) {
		void *temp = getBSTNODEvalue(largest);
		setBSTNODEvalue(largest, getBSTNODEvalue(i));
		setBSTNODEvalue(i, temp);
		heapify(h, largest);
	}
}

static STACK *bftraverse(HEAP *h) { // breadth-first traversal of the heap's tree
	STACK *s = newSTACK(h->display, NULL); // stack to store output values
	if(sizeHEAP(h) == 0) {
		return s; // nothing to traverse so return an empty stack
	}
	QUEUE *q = newQUEUE(h->display, NULL); // queue for traversal
	BSTNODE *n; // currently visited node
	enqueue(q, getBSTroot(h->tree)); // start at the root
	while(sizeQUEUE(q) > 0) {
		n = dequeue(q);
		push(s, n); // put the node on the stack
		if(getBSTNODEleft(n) != NULL) {
			enqueue(q, getBSTNODEleft(n));
		}
		if(getBSTNODEright(n) != NULL) {
			enqueue(q, getBSTNODEright(n));
		}
	}
	freeQUEUE(q);
	return s;
}

void *peekHEAP(HEAP *h) {
	return getBSTNODEvalue(getBSTroot(h->tree));
}

void *extractHEAP(HEAP *h) {
	// Algorithm: Cormen et al. 163
	assert(sizeHEAP(h) > 0);

	BSTNODE *root = getBSTroot(h->tree);
	void *val = getBSTNODEvalue(root); // store the current value of the root
	if(sizeHEAP(h) != 1) {
		BSTNODE *last = pop(h->nodestack);
		setBSTNODEvalue(root, getBSTNODEvalue(last)); // move the last value into the root

		// get rid of the last node
		BSTNODE *parent = getBSTNODEparent(last);
		if(getBSTNODEleft(parent) == last) {
			setBSTNODEleft(parent, NULL);
		}
		else {
			setBSTNODEright(parent, NULL);
		}
		freeBSTNODE(last, NULL);
	}
	else {
		freeBSTNODE(root, NULL);
	}
	setBSTsize(h->tree, sizeBST(h->tree) - 1);

	if(sizeHEAP(h) > 1) {
		heapify(h, root); // heapify from the new root
	}
	return val; // return the old value of the root
}

int sizeHEAP(HEAP *h) {
	return sizeBST(h->tree);
}

void displayHEAP(HEAP *h, FILE *fp) {
	displayBST(h->tree, fp);
}

void displayHEAPdebug(HEAP *h, FILE *fp) {
	fprintf(fp, "heap size: %i\n",sizeHEAP(h));
	fprintf(fp, "bst size: %i\n",sizeBST(h->tree));
	displayBSTdebug(h->tree, fp);
}

void freeHEAP(HEAP *h) {
	while(sizeHEAP(h) > 0) {
		void *v = extractHEAP(h);
		if(h->f != NULL) {
			h->f(v);
		}
	}
	free(h->tree);
	freeSTACK(h->nodestack);
	free(h);
}
