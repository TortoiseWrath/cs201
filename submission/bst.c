#include "bst.h"
#include <assert.h>
#include <stdlib.h>
#include "queue.h"

struct bstnode {
	void *value;
	BSTNODE *left;
	BSTNODE *right;
	BSTNODE *parent;
};

struct bst {
	BSTNODE *root;
	int size;
	void (*display)(void *, FILE *);
	int (*comparator)(void *, void *);
	void (*swapper)(BSTNODE *, BSTNODE *);
	void (*f)(void *);
};

static void genericSwapper(BSTNODE *a, BSTNODE *b);
static int maxDepth(BSTNODE *n);
static int minDepth(BSTNODE *n);
static void displaySubtree(BSTNODE *n, FILE *fp, void (*display)(void *, FILE *));

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

void setBSTNODEparent(BSTNODE *n, BSTNODE *replacement) {
	n->parent = replacement;
	return;
}

void freeBSTNODE(BSTNODE *n, void (*f)(void *)) {
	if(f != NULL) f(getBSTNODEvalue(n));
	free(n);
	return;
}

BST *newBST(
	void (*display)(void *, FILE *),
	int (*comparator)(void *, void *),
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
	return z;
}

BSTNODE *findBST(BST *t, void *value) {
	//Algorithm: Cormen et al. 291
	BSTNODE *x = getBSTroot(t);
	while(x != NULL && t->comparator(value, getBSTNODEvalue(x)) != 0) {
		if (t->comparator(value, getBSTNODEvalue(x)) < 0) { // k < x
			x = getBSTNODEleft(x);
		}
		else {
			x = getBSTNODEright(x);
		}
	}
	return x;
}

BSTNODE *deleteBST(BST *t, void *value) {
	/* printf("Deleting ");
	t->display(value,stdout);
	printf("\n"); */
	BSTNODE *x = findBST(t, value);
	x = swapToLeafBST(t, x);
	pruneLeafBST(t, x);
	setBSTsize(t, sizeBST(t) - 1); // decrement tree size
	/* printf("Deleted ");
	t->display(getBSTNODEvalue(x),stdout);
	printf("\n");
	displayBSTdecorated(t, stdout); */
	return x;
}

static BSTNODE *successorBST(BSTNODE *n);
static BSTNODE *predecessorBST(BSTNODE *n);
static BSTNODE *swaptoPredecessorBST(BST *t, BSTNODE *n);
static BSTNODE *swaptoSuccessorBST(BST *t, BSTNODE *n);

BSTNODE *swapToLeafBST(BST *t, BSTNODE *node) {
	if(node == NULL || (getBSTNODEleft(node) == NULL && getBSTNODEright(node) == NULL)) {
		return node;
	}

	BSTNODE *x = successorBST(node);
	if(x == NULL) {
		x = predecessorBST(node);
		t->swapper(node, x); // swap VALUES, not nodes
		return swaptoPredecessorBST(t, x);
	}
	else {
	t->swapper(node, x); // swap VALUES, not nodes
		return swaptoSuccessorBST(t, x);
	}
}

BSTNODE *swaptoPredecessorBST(BST *t, BSTNODE *node) {
	if(node == NULL || (getBSTNODEleft(node) == NULL && getBSTNODEright(node) == NULL)) {
		return node;
	}

	BSTNODE *x = predecessorBST(node);
	if(x == NULL) {
		return swapToLeafBST(t, x);
	}
	// printf("Swapping %p to leaf; predecessor is %p\n", node, x);
	t->swapper(node, x);
	return swaptoPredecessorBST(t, x);
}

BSTNODE *swaptoSuccessorBST(BST *t, BSTNODE *node) {
	if(node == NULL || (getBSTNODEleft(node) == NULL && getBSTNODEright(node) == NULL)) {
		return node;
	}

	BSTNODE *x = successorBST(node);
	if(x == NULL) {
		return swapToLeafBST(t, x);
	}
	// printf("Swapping %p to leaf; successor is %p\n", node, x);
	t->swapper(node, x);
	return swaptoSuccessorBST(t, x);
}

BSTNODE *successorBST(BSTNODE *node) {
	BSTNODE *n = node;
	if(getBSTNODEright(n) != NULL) {
		// Minimum value of right subtree
		n = getBSTNODEright(n);
		while(getBSTNODEleft(n) != NULL) {
			n = getBSTNODEleft(n);
		}
		return n;
	}

	BSTNODE *p = getBSTNODEparent(n);
	while(p != NULL && p != n && getBSTNODEright(p) == n) {
		n = p;
		p = getBSTNODEparent(p);
	}
	return (p == n )? NULL : p;
}

BSTNODE *predecessorBST(BSTNODE *node) {
	BSTNODE *n = node;
	if(getBSTNODEleft(n) != NULL) {
		// Maximum value of left subtree
		n = getBSTNODEleft(n);
		while(getBSTNODEright(n) != NULL) {
			n = getBSTNODEright(n);
		}
		return n;
	}

	BSTNODE *p = getBSTNODEparent(n);
	while(p != NULL && p != n && getBSTNODEleft(p) == n) {
		n = p;
		p = getBSTNODEparent(p);
	}
	return p == n ? NULL : p;
}

void pruneLeafBST(BST *t, BSTNODE *leaf) {
	assert(getBSTNODEleft(leaf) == NULL);
	assert(getBSTNODEright(leaf) == NULL);

	if(getBSTNODEparent(leaf) == NULL) { // is root node
		setBSTroot(t, NULL); // empty the tree
		return;
	}

	BSTNODE *parent = getBSTNODEparent(leaf);
	if(getBSTNODEleft(parent) == leaf) {
		setBSTNODEleft(parent, NULL);
	}
	else {
		setBSTNODEright(parent, NULL);
	}
	return;
}

int sizeBST(BST *t) {
	return t->size;
}

void statisticsBST(BST *t, FILE *fp) {
	fprintf(fp, "Nodes: %i\n", sizeBST(t));
	fprintf(fp, "Minimum depth: %i\n", minDepth(getBSTroot(t)));
	fprintf(fp, "Maximum depth: %i\n", maxDepth(getBSTroot(t)));
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

static void displayBSTlevelorder(BST *t, FILE *fp, int decorated) {
	if(sizeBST(t) == 0) {
		return;
	}
	QUEUE *q1 = newQUEUE(NULL, NULL);
	QUEUE *q2 = newQUEUE(NULL, NULL);
	enqueue(q1, getBSTroot(t));
	int level = 0;
	int endoflevel = 1;
	while(sizeQUEUE(q1) > 0) {
		if(decorated && endoflevel) { // if the current level has not yet been displayed
			fprintf(fp, "%i: ",level);
			endoflevel = 0;
		}
		BSTNODE *n = dequeue(q1);
		if(decorated) {
			if(getBSTNODEleft(n) == NULL && getBSTNODEright(n) == NULL) { // is leaf
				fputc('=', fp);
			}
			t->display(getBSTNODEvalue(n), fp); // display the node value
			fputc('(', fp);
			if(getBSTNODEparent(n) == NULL || getBSTNODEparent(n) == n) { // is root
				t->display(getBSTNODEvalue(n), fp);
				fputs(")X", fp);
			}
			else { // is child
				t->display(getBSTNODEvalue(getBSTNODEparent(n)), fp); // display parent value
				fputc(')', fp);
				if(getBSTNODEleft(getBSTNODEparent(n)) == n) { // is left child
					fputc('L', fp);
				}
				else { // is right child
					fputc('R', fp);
				}
			}
		}
		else {
			t->display(getBSTNODEvalue(n), fp); // non-decorated display
		}
		if(sizeQUEUE(q1) == 0) { // reached end of level
			fputc('\n', fp);
			level++;
			endoflevel = 1;
		}
		else {
			fputc(' ', fp);
		}
		if(getBSTNODEleft(n)) enqueue(q2, getBSTNODEleft(n));
		if(getBSTNODEright(n)) enqueue(q2, getBSTNODEright(n));
		if(sizeQUEUE(q1) == 0) {
			freeQUEUE(q1);
			q1 = q2;
			q2 = newQUEUE(NULL, NULL);
		}
	}
	freeQUEUE(q1);
	freeQUEUE(q2);
	return;
}

void displayBSTdebug(BST *t, FILE *fp) {
	displayBSTlevelorder(t, fp, 0);
	return;
}

void displayBSTdecorated(BST *t, FILE *fp) {
	displayBSTlevelorder(t, fp, 1);
	return;
}


void freeBST(BST *t) {
	while(sizeBST(t) > 0) {
		BSTNODE *n = deleteBST(t, getBSTNODEvalue(getBSTroot(t))); //delete the root (easy to find)
		freeBSTNODE(n, t->f); //free the old root
	}
	free(t);
}
