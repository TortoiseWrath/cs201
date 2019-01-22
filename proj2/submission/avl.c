#include "avl.h"
#include "bst.h"
#include <assert.h>
#include <stdlib.h>

struct avl {
	BST *bst;
	void (*display)(void *, FILE *);
	int (*comparator)(void *, void *);
	void (*release)(void *);
	int netInsertions;
};

typedef struct avlval AVLVALUE;
struct avlval {
	void *value;
	int frequency;
	int height;
	int leftheight;
	int rightheight;
	void (*display)(void *, FILE *);
	int (*comparator)(void *, void *);
	void (*release)(void *);
};

static void swapAVLVALUE(BSTNODE *, BSTNODE *);
static void displayAVLVALUE(void *, FILE *);
static int compareAVLVALUE(void *, void *);
static void freeAVLVALUE(void *);
static AVLVALUE *newAVLVALUE(void *, void (*)(void *, FILE *), int (*)(void *, void *), void (*)(void *));
static int frequencyAVLVALUE(AVLVALUE *);
static int heightAVLVALUE(AVLVALUE *);
static int leftheightAVLVALUE(AVLVALUE *);
static int rightheightAVLVALUE(AVLVALUE *);
static int balanceAVLVALUE(AVLVALUE *);
static void setAVLVALUEfrequency(AVLVALUE *, int);
static void setAVLVALUEheight(AVLVALUE *, int);
static void setAVLVALUEleftheight(AVLVALUE *, int);
static void setAVLVALUErightheight(AVLVALUE *, int);
static void setAVLVALUEbalance(BSTNODE *);
static void *valueAVLVALUE(AVLVALUE *);
static BSTNODE *findAVLNODE(AVL *, void *);
static int AVLlinear(BSTNODE *, BSTNODE *, BSTNODE *);
static void AVLrotate(BSTNODE *, BSTNODE *, BST *);

AVL *newAVL(void (*d)(void *, FILE *), int (*c)(void *, void *), void (*f)(void *)) {
	AVL *tree = malloc(sizeof(AVL));
	assert(tree != NULL);
	tree->bst = newBST(displayAVLVALUE, compareAVLVALUE, swapAVLVALUE, freeAVLVALUE);
	tree->display = d;
	tree->comparator = c;
	tree->release = f;
	tree->netInsertions = 0;
	return tree;
}

static void insertionFixUp(BSTNODE *x, BST *t) {
	for(;;) {
		if(getBSTNODEparent(x) == NULL || getBSTNODEparent(x) == x) {
			// x is the root
			break;
		}
		int position = 1 - 2*(getBSTNODEright(getBSTNODEparent(x)) == x);
			// x is left child: position = 1
			// x is right child: position = -1
		if(balanceAVLVALUE(getBSTNODEvalue(getBSTNODEparent(x))) == -1 * position) {
			// parent favors the sibling - case 1
			setAVLVALUEbalance(getBSTNODEparent(x));
			break;
		}
		else if(balanceAVLVALUE(getBSTNODEvalue(getBSTNODEparent(x))) == 0) {
			// parent has no favorite - case 2
			setAVLVALUEbalance(getBSTNODEparent(x));
			x = getBSTNODEparent(x);
			continue;
		}
		else {
			// parent favors x
			assert(balanceAVLVALUE(getBSTNODEvalue(getBSTNODEparent(x))) == position);
			BSTNODE *y = NULL;
			if(balanceAVLVALUE(getBSTNODEvalue(x)) == 1) {
				// left child is the favorite
				y = getBSTNODEleft(x);
			}
			else if(balanceAVLVALUE(getBSTNODEvalue(x)) == -1) {
				// right child is the favorite
				y = getBSTNODEright(x);
			}
			BSTNODE *p = getBSTNODEparent(x);
			if(y != NULL && !AVLlinear(y, x, p)) {
				// case 3
				AVLrotate(y, x, t);
				AVLrotate(y, p, t);
				setAVLVALUEbalance(x);
				setAVLVALUEbalance(p);
				setAVLVALUEbalance(y);
			}
			else {
				AVLrotate(x, p, t);
				setAVLVALUEbalance(p);
				setAVLVALUEbalance(x);
			}
			break;
		}
	}
	return;
}

static void deletionFixUp(BSTNODE *x, BST *t) {
	setAVLVALUEheight(getBSTNODEvalue(x), 0);
	for(;;) {
		if(getBSTNODEparent(x) == NULL || getBSTNODEparent(x) == x) {
			// x is the root
			break;
		}
		int position = 1 - 2*(getBSTNODEright(getBSTNODEparent(x)) == x);
			// x is left child: position = 1
			// x is right child: position = -1
		if(balanceAVLVALUE(getBSTNODEvalue(getBSTNODEparent(x))) == position) {
			// parent favors x - case 1
			setAVLVALUEbalance(getBSTNODEparent(x));
			x = getBSTNODEparent(x);
			continue;
		}
		else if(balanceAVLVALUE(getBSTNODEvalue(getBSTNODEparent(x))) == 0) {
			// parent has no favorite - case 2
			setAVLVALUEbalance(getBSTNODEparent(x));
			break;
		}
		else {
			// parent favors sibling
			assert(balanceAVLVALUE(getBSTNODEvalue(getBSTNODEparent(x))) == -1 * position);
			BSTNODE *p = getBSTNODEparent(x);
			BSTNODE *z = getBSTNODEleft(getBSTNODEparent(x));
			if(z == x) z = getBSTNODEright(getBSTNODEparent(x)); // z = sibling
			BSTNODE *y = NULL;
			if(balanceAVLVALUE(getBSTNODEvalue(z)) == 1) {
				// left child is the favorite
				y = getBSTNODEleft(z);
			}
			else if(balanceAVLVALUE(getBSTNODEvalue(z)) == -1) {
				// right child is the favorite
				y = getBSTNODEright(z);
			}
			if(y != NULL && !AVLlinear(y, z, p)) {
				// case 3
				AVLrotate(y, z, t);
				AVLrotate(y, p, t);
				setAVLVALUEbalance(p);
				setAVLVALUEbalance(z);
				setAVLVALUEbalance(y);
				x = y;
				continue;
			}
			else {
				// case 4
				AVLrotate(z, p, t);
				setAVLVALUEbalance(p);
				setAVLVALUEbalance(z);
				if(y == NULL) {
					break;
				}
				x = z;
				continue;
			}
		}
	}
}

void insertAVL(AVL *tree, void *value) {
	tree->netInsertions++;
	BSTNODE *n = findAVLNODE(tree, value);
	if(n != NULL) {
		// Increment frequency of existing value
		AVLVALUE *avlval = getBSTNODEvalue(n);
		setAVLVALUEfrequency(avlval, frequencyAVLVALUE(avlval) + 1);
		// Newly-passed value must be freed by calling function.
		return;
	}

	// Based on: http://beastie.cs.ua.edu/avl/insert-avl.html

	// Insert new value into BST
	AVLVALUE *avlval = newAVLVALUE(value, tree->display, tree->comparator, tree->release);
	BSTNODE *x = insertBST(tree->bst, avlval);

	// Set the balance of the newly inserted node
	setAVLVALUEbalance(x);
	assert(leftheightAVLVALUE(getBSTNODEvalue(x)) == 0);
	assert(rightheightAVLVALUE(getBSTNODEvalue(x)) == 0);
	assert(heightAVLVALUE(getBSTNODEvalue(x)) == 1);

	insertionFixUp(x, tree->bst);
	return;
}

int findAVLcount(AVL *tree, void *value) {
	BSTNODE *avlval = findAVLNODE(tree, value);
	if(avlval == NULL) {
		return 0;
	}
	return frequencyAVLVALUE(getBSTNODEvalue(avlval));
}

void *findAVL(AVL *tree, void *value) {
	BSTNODE *avlval = findAVLNODE(tree, value);
	if(avlval == NULL) {
		return NULL;
	}
	return value; // guaranteed to be the same as the value of avlval by assertion in findAVLNODE
}

void *deleteAVL(AVL *tree, void *value) {
	BSTNODE *n = findAVLNODE(tree, value);
	if(n == NULL) {
		return NULL;
	}
	AVLVALUE *avlval = getBSTNODEvalue(n);
	tree->netInsertions--;
	int frequency = frequencyAVLVALUE(avlval);
	if(frequency > 1) {
		setAVLVALUEfrequency(avlval, frequency - 1);
		return NULL;
	}

	// Based on http://beastie.cs.ua.edu/avl/delete-avl.html
	BSTNODE *x = swapToLeafBST(tree->bst, n);
	deletionFixUp(x, tree->bst);

	// Prune
	pruneLeafBST(tree->bst, x);
	setBSTsize(tree->bst, sizeBST(tree->bst) - 1);
	avlval = getBSTNODEvalue(x);
	free(x);
	void *v = valueAVLVALUE(avlval);
	free(avlval);
	return v;
}

int sizeAVL(AVL *tree) {
	return sizeBST(tree->bst);
}

int duplicatesAVL(AVL *tree) {
	return tree->netInsertions - sizeAVL(tree);
}

void statisticsAVL(AVL *tree, FILE *fp) {
	fprintf(fp, "Duplicates: %i\n", duplicatesAVL(tree));
	statisticsBST(tree->bst, fp);
	return;
}

void displayAVL(AVL *tree, FILE *fp) {
	if(sizeAVL(tree) == 0) {
		// fputs("EMPTY\n", fp);
		return;
	}
	displayBSTdecorated(tree->bst, fp);
	return;
}

void displayAVLdebug(AVL *tree, FILE *fp) {
	displayBST(tree->bst, fp);
	return;
}

void freeAVL(AVL *tree) {
	freeBST(tree->bst);
	free(tree);
	return;
}

static void swapAVLVALUE(BSTNODE *a, BSTNODE *b) {
	AVLVALUE *ta = getBSTNODEvalue(a);
	AVLVALUE *tb = getBSTNODEvalue(b);

	// swap the values
	void *vtemp = valueAVLVALUE(ta);
	ta->value = valueAVLVALUE(tb);
	tb->value = vtemp;

	// swap the frequencies
	int ftemp = frequencyAVLVALUE(ta);
	setAVLVALUEfrequency(ta, frequencyAVLVALUE(tb));
	setAVLVALUEfrequency(tb, ftemp);

	// AVL heights and balance factors are NOT swapped

	return;
}

static void displayAVLVALUE(void /*AVLVALUE*/ *v, FILE *fp) {
	AVLVALUE *avlval = v;
	avlval->display(valueAVLVALUE(avlval), fp);
	if(frequencyAVLVALUE(avlval) > 1) {
		fprintf(fp,"[%i]",frequencyAVLVALUE(avlval));
	}
	if(balanceAVLVALUE(avlval) != 0) {
		fputc((balanceAVLVALUE(avlval) > 0)?'+':'-', fp);
	}
	return;
}

static int compareAVLVALUE(void /*AVLVALUE*/ *a, void /*AVLVALUE*/ *b) {
	AVLVALUE *avlvala = a;
	AVLVALUE *avlvalb = b;
	return avlvala->comparator(avlvala->value, avlvalb->value);
}

static void freeAVLVALUE(void /*AVLVALUE*/ *v) {
	AVLVALUE *avlval = v;
	if(avlval->release != NULL) {
		avlval->release(avlval->value);
	}
	free(avlval);
	return;
}

static AVLVALUE *newAVLVALUE(void *value, void (*d)(void *, FILE *), int (*c)(void *, void *), void (*f)(void *)) {
	AVLVALUE *avlval = malloc(sizeof(AVLVALUE));
	assert(avlval != NULL);
	avlval->value = value;
	setAVLVALUEfrequency(avlval, 1);
	setAVLVALUEheight(avlval, -1);
	setAVLVALUEleftheight(avlval, -1);
	setAVLVALUErightheight(avlval, -1);
	avlval->display = d;
	avlval->comparator = c;
	avlval->release = f;
	return avlval;
}

static int frequencyAVLVALUE(AVLVALUE *avlval) {
	return avlval->frequency;
}

static int heightAVLVALUE(AVLVALUE *avlval) {
	return avlval->height;
}

static int leftheightAVLVALUE(AVLVALUE *avlval) {
	return avlval->leftheight;
}

static int rightheightAVLVALUE(AVLVALUE *avlval) {
	return avlval->rightheight;
}

static int balanceAVLVALUE(AVLVALUE *avlval) {
	return leftheightAVLVALUE(avlval) - rightheightAVLVALUE(avlval);
}

static void setAVLVALUEfrequency(AVLVALUE *avlval, int freq) {
	avlval->frequency = freq;
	return;
}

static void setAVLVALUEheight(AVLVALUE *avlval, int height) {
	avlval->height = height;
	return;
}

static void setAVLVALUEleftheight(AVLVALUE *avlval, int height) {
	avlval->leftheight = height;
	return;
}

static void setAVLVALUErightheight(AVLVALUE *avlval, int height) {
	avlval->rightheight = height;
	return;
}

static void setAVLVALUEbalance(BSTNODE *n) {
	AVLVALUE *avlval = getBSTNODEvalue(n);
	if(getBSTNODEleft(n) != NULL) {
		setAVLVALUEleftheight(avlval, heightAVLVALUE(getBSTNODEvalue(getBSTNODEleft(n))));
	}
	else {
		setAVLVALUEleftheight(avlval, 0);
	}
	if(getBSTNODEright(n) != NULL) {
		setAVLVALUErightheight(avlval, heightAVLVALUE(getBSTNODEvalue(getBSTNODEright(n))));
	}
	else {
		setAVLVALUErightheight(avlval, 0);
	}
	if(leftheightAVLVALUE(avlval) > rightheightAVLVALUE(avlval)) {
		setAVLVALUEheight(avlval, leftheightAVLVALUE(avlval) + 1);
	}
	else {
		setAVLVALUEheight(avlval, rightheightAVLVALUE(avlval) + 1);
	}
	return;
}

static void *valueAVLVALUE(AVLVALUE *avlval) {
	return avlval->value;
}

static BSTNODE *findAVLNODE(AVL *tree, void *value) {
	AVLVALUE *compareTo = newAVLVALUE(value, tree->display, tree->comparator, NULL);
	BSTNODE *result = findBST(tree->bst, compareTo);
	free(compareTo);
	assert(result == NULL || tree->comparator(valueAVLVALUE(getBSTNODEvalue(result)), value) == 0);
	return result;
}

static int AVLlinear(BSTNODE *a, BSTNODE *b, BSTNODE *c) {
	return (getBSTNODEleft(c) == b && getBSTNODEleft(b) == a)
		|| (getBSTNODEright(c) == b && getBSTNODEright(b) == a);
}

static void AVLrotate(BSTNODE *a, BSTNODE *b, BST *bst) {
	BSTNODE *c, *p;
	if(getBSTNODEleft(b) == a) {
		// rotate right
		c = getBSTNODEright(a);
		p = getBSTNODEparent(b);
		setBSTNODEleft(b, c);
		setBSTNODEright(a, b);
	}
	else if(getBSTNODEright(b) == a) {
		// rotate left
		c = getBSTNODEleft(a);
		p = getBSTNODEparent(b);
		setBSTNODEright(b, c);
		setBSTNODEleft(a, b);
	}
	else assert(0); // panic

	setBSTNODEparent(a, p);
	setBSTNODEparent(b, a);
	if(c != NULL) setBSTNODEparent(c, b);
	if(p == NULL || p == b) {
		setBSTroot(bst, a);
		setBSTNODEparent(a, a);
	}
	else {
		if(getBSTNODEleft(p) == b) {
			setBSTNODEleft(p, a);
		}
		else {
			setBSTNODEright(p, a);
		}
	}

	return;
}
