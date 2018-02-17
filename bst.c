#include "bst.h"
#include <assert.h>
#include <malloc.h>
#include "queue.h"

struct bstnode {
	void *value;
	BSTNODE *left;
	BSTNODE *right;
	BSTNODE *parent;
};

static void genericSwapper(BSTNODE *a, BSTNODE *b);
static void maxDepth(BSTNODE *n);
static void minDepth(BSTNODE *n);
static void displaySubtree(BSTNODE *n, FILE *fp, void (*display)(void *, FILE *));
static void displaySubtreeDebug(BSTNODE *n, FILE *fp, void (*display)(void *, FILE *));

BSTNODE *newBSTNODE(void *v) {
	BSTNODE *node = malloc(sizeof(BSTNODE));
	assert(node != NULL); // The memory allocated shall not be null.
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->value = v;
	return node;
}

void *getBSTNODEvalue(BSTNODE *n) {
	assert(n->value != NULL);
	return n->value;
}

void setBSTNODEvalue(BSTNODE *n, void *value) {
	n->value = value;
	return;
}

BSTNODE *getBSTNODEleft(BSTNODE *n) {
	return n->left;
}

void setBSTNODEleft(BSTNODE *n, BSTNODE *replacement) {
	n->left = replacement;
	return;
}

BSTNODE *getBSTNODEright(BSTNODE *n) {
	return n->right;
}

void setBSTNODEright(BSTNODE *n, BSTNODE *replacement) {
	n->right = replacement;
	return;
}

BSTNODE *getBSTNODEparent(BSTNODE *n) {
	return n->parent;
}

void setBSTNODEparent(BSTNODE *n,B STNODE *replacement) {
	n->parent = replacement;
	return;
}

void freeBSTNODE(BSTNODE *n, void (*f)(void *)) {
	if(f != NULL) f(n);
	free(n);
	return;
}

struct BST {
	BSTNODE *root;
	int size;
	void (*display)(void *, FILE *);
	int (*comparator)(void *, void *);
	void (*swapper)(BSTNODE *, BSTNODE *);
	void (*f)(void *);
};

BST *newBST(
	void (*display)(void *, FILE *),
	void (*comparator)(void *, void *),
	void (*swapper)(BSTNODE *, BSTNODE *),
	void (*f)(void *)
) {
	BST *tree = malloc(sizeof(BST));
	assert(tree != NULL); // The memory allocated shall not be null.
	tree->root = NULL;
	tree->size = 0;
	tree->display = display;
	tree->comparator = comparator;
	tree->swapper = swapper;
	if(swapper == NULL) {
		tree->swapper = genericSwapper;
	}
	tree->f = f;
	return tree;
}

static void genericSwapper(BSTNODE *a, BSTNODE *b) {
	void *temp = getBSTNODEvalue(a);
	setBSTNODEvalue(a, getBSTNODEvalue(b));
	setBSTNODEvalue(b, temp);
	return;
}

BSTNODE *getBSTroot(BST *t) {
	return t->root;
}

void setBSTroot(BST *t, BSTNODE *replacement) {
	t->root = replacement;
	return;
}

void setBSTsize(BST *t, int s) {
	t->size = s;
	return;
}

BSTNODE *insertBST(BST *t, void *value) {
	//Algorithm: Cormen et al. 294
	BSTNODE *z = newBSTNODE(value);
	BSTNODE *y = NULL;
	BSTNODE *x = getBSTroot(t);
	while(x != NULL) {
		y = x;
		if (t->comparator(value, getBSTNODEvalue(x)) < 0) { // z < x
			x = getBSTNODEleft(x);
		}
		else {
			x = getBSTNODEright(x);
		}
	}
	setBSTNODEparent(z, y);
	if(y == NULL) {
		//tree was empty
		setBSTroot(t, z);
	}
	else if(t->comparator(value, getBSTNODEvalue(y)) < 0) {  // z < y
		setBSTNODEleft(y, z);
	}
	else {
		setBSTNODEright(y, z);
	}

	//Increment the size of the tree
	setBSTsize(t, sizeBST(t) + 1);
}

BSTNODE *findBST(BST *t, void *value) {
	//Algorithm: Cormen et al. 291
	BSTNODE *x = getBSTroot(t);
	while(x != NULL && comparator(value, getBSTNODEvalue(x)) != 0) {
		if (comparator(value, getBSTNODEvalue(x)) < 0) { // k < x
			x = getBSTNODEleft(x);
		}
		else {
			x = getBSTNODEright(x);
		}
	}
	return x;
}

BSTNODE *deleteBST(BST *t, void *value) {
	BSTNODE *x = findBST(t, value);
	x = swapToLeafBST(t, x);
	pruneLeafBST(t, x);
	return x;
}

BSTNODE *swapToLeafBST(BST *t, BSTNODE *node) {
	if(node == NULL || getBSTNODEleft(node) == NULL && getBSTNODEright(node) == NULL) {
		return node;
	}

	if(getBSTNODEright(node) == NULL) {
		// No successor: find predecessor
		BSTNODE *x = getBSTNODEleft(node);
		while(getBSTNODEright(x) != NULL) {
			x = getBSTNODEright(x);
		}
		// x is predecessor
		t->swapper(node, x); // swap VALUES, not nodes
		return swapToLeafBST(t, x);
	}

	// Find successor
	BSTNODE *x = getBSTNODEright(node);
	while(getBSTNODEleft(x) != NULL) {
		x = getBSTNODEleft(x);
	}
	// x is successor
	t->swapper(node, x); // swap VALUES, not nodes
	return swapToLeafBST(t, x);
}

void pruneLeafBST(BST *t, BSTNODE *leaf) {
	assert(getBSTNODEleft(leaf) == NULL);
	assert(getBSTNODEright(leaf) == NULL);

	if(getBSTNODEparent(leaf) == NULL) { // is root node
		setBSTroot(t, NULL); // empty the tree
		setBSTsize(t, 0); // inform the tree it is empty
		return;
	}

	BSTNODE *parent = getBSTNODEparent(leaf);
	if(getBSTNODEleft(parent) == leaf) {
		setBSTNODEleft(parent, NULL);
	}
	else {
		setBSTNODEright(parent, NULL);
	}
	setBSTsize(t, sizeBST(t) - 1); // decrement tree size
	return;
}

int sizeBST(BST *t) {
	return t->size;
}

void statisticsBST(BST *t, FILE *fp) {
	fprintf(fp, "Nodes: %i\n", sizeBST(t));
	fprintf(fp, "Minimum depth: %i\n", minDepth(getBSTroot(t)));
	fprintf(fp, "Maximum depth: %i\n", minDepth(getBSTroot(t)));
}

int maxDepth(BSTNODE *n) {
	if(n == NULL) return -1;
	int left = maxDepth(getBSTNODEleft(n)) + 1;
	int right = maxDepth(getBSTNODEright(n)) + 1;
	if(left < right) return right;
	else return left;
}

int minDepth(BSTNODE *n) {
	if(n == NULL) return -1;
	int left = minDepth(getBSTNODEleft(n)) + 1;
	int right = minDepth(getBSTNODEright(n)) + 1;
	if(left < right) return left;
	else return right;
}

void displayBST(BST *t, FILE *fp) {
	fputc('[', fp);
	displaySubtree(getBSTroot(t), fp, t->display);
	fputc(']', fp);
	return;
}

static void displaySubtree(BSTNODE *root, FILE *fp, void (*display)(void *, FILE *)) {
	if(root == NULL) return;
	display(getBSTNODEvalue(root), fp);
	if(getBSTNODEleft(root) != NULL) {
		fputs(" [", fp);
		displaySubtree(getBSTNODEleft(root), fp, display);
		fputc(']', fp);
	}
	if(getBSTNODEright(root) != NULL) {
		fputs(" [", fp);
		displaySubtree(getBSTNODEright(root), fp, display);
		fputc(']', fp);
	}
}

void displayBSTdebug(BST *t, FILE *fp) {
	if(sizeBST(t) == 0) return;
	QUEUE *q = newQUEUE(NULL, NULL);
	enqueue(q, root);
	while(sizeQUEUE(q) > 0) {
		BSTNODE *n = dequeue(q);
		t->display(getBSTNODEvalue(n), fp);
		if(getBSTNODEleft(n) != NULL) {
			enqueue(q, getBSTNODEleft(n));
		}
		if(getBSTNODEright(n) != NULL) {
			enqueue(q, getBSTNODEright(n));
		}
	}
	freeQUEUE(q);
	return;
}


void freeBST(BST *t) {
 //todo
}
