#include "gst.h"
#include "bst.h"
#include <assert.h>
#include <stdlib.h>

struct gst {
	BST *bst;
	void (*display)(void *, FILE *);
	int (*comparator)(void *, void *);
	void (*release)(void *);
	int netInsertions;
};

typedef struct gstval GSTVALUE;
struct gstval {
	void *value;
	int frequency;
	void (*display)(void *, FILE *);
	int (*comparator)(void *, void *);
	void (*release)(void *);
};

static void swapGSTVALUE(BSTNODE *, BSTNODE *);
static void displayGSTVALUE(void *, FILE *);
static int compareGSTVALUE(void *, void *);
static void freeGSTVALUE(void *);
static GSTVALUE *newGSTVALUE(void *, void (*)(void *, FILE *), int (*)(void *, void *), void (*)(void *));
static int frequencyGSTVALUE(GSTVALUE *);
static void setGSTVALUEfrequency(GSTVALUE *, int);
static void *valueGSTVALUE(GSTVALUE *);
static BSTNODE *findGSTNODE(GST *, void *);

GST *newGST(void (*d)(void *, FILE *), int (*c)(void *, void *), void (*f)(void *)) {
	GST *tree = malloc(sizeof(GST));
	assert(tree != NULL);
	tree->bst = newBST(displayGSTVALUE, compareGSTVALUE, swapGSTVALUE, freeGSTVALUE);
	tree->display = d;
	tree->comparator = c;
	tree->release = f;
	tree->netInsertions = 0;
	return tree;
}

void insertGST(GST *tree, void *value) {
	tree->netInsertions++;
	BSTNODE *n = findGSTNODE(tree, value);
	if(n != NULL) {
		// Increment frequency of existing value
		GSTVALUE *gstval = getBSTNODEvalue(n);
		setGSTVALUEfrequency(gstval, frequencyGSTVALUE(gstval) + 1);
		// Newly-passed value must be freed by calling function.
		return;
	}
	// Insert new value into BST
	GSTVALUE *gstval = newGSTVALUE(value, tree->display, tree->comparator, tree->release);
	insertBST(tree->bst, gstval);
	return;
}

int findGSTcount(GST *tree, void *value) {
	BSTNODE *gstval = findGSTNODE(tree, value);
	if(gstval == NULL) {
		return 0;
	}
	return frequencyGSTVALUE(getBSTNODEvalue(gstval));
}

void *findGST(GST *tree, void *value) {
	BSTNODE *gstval = findGSTNODE(tree, value);
	if(gstval == NULL) {
		return NULL;
	}
	return value; // guaranteed to be the same as the value of gstval by assertion in findGSTNODE
}

void *deleteGST(GST *tree, void *value) {
	BSTNODE *n = findGSTNODE(tree, value);
	if(n == NULL) {
		return NULL;
	}
	GSTVALUE *gstval = getBSTNODEvalue(n);
	tree->netInsertions--;
	int frequency = frequencyGSTVALUE(gstval);
	if(frequency > 1) {
		setGSTVALUEfrequency(gstval, frequency - 1);
		return NULL;
	}
	n = deleteBST(tree->bst, gstval);
	gstval = getBSTNODEvalue(n);
	free(n);
	void *v = valueGSTVALUE(gstval);
	free(gstval);
	return v;
}

int sizeGST(GST *tree) {
	return sizeBST(tree->bst);
}

int duplicates(GST *tree) {
	return tree->netInsertions - sizeGST(tree);
}

void statisticsGST(GST *tree, FILE *fp) {
	fprintf(fp, "Duplicates: %i\n", duplicates(tree));
	statisticsBST(tree->bst, fp);
	return;
}

void displayGST(GST *tree, FILE *fp) {
	if(sizeGST(tree) == 0) {
		// fputs("EMPTY\n", fp);
		return;
	}
	displayBSTdecorated(tree->bst, fp);
	return;
}

void displayGSTdebug(GST *tree, FILE *fp) {
	displayBST(tree->bst, fp);
	return;
}

void freeGST(GST *tree) {
	freeBST(tree->bst);
	free(tree);
	return;
}

static void swapGSTVALUE(BSTNODE *a, BSTNODE *b) {
	void *temp = getBSTNODEvalue(a);
	setBSTNODEvalue(a, getBSTNODEvalue(b));
	setBSTNODEvalue(b, temp);
	return;
}

static void displayGSTVALUE(void /*GSTVALUE*/ *v, FILE *fp) {
	GSTVALUE *gstval = v;
	gstval->display(valueGSTVALUE(gstval), fp);
	if(frequencyGSTVALUE(gstval) > 1) {
		fprintf(fp,"[%i]",frequencyGSTVALUE(gstval));
	}
	return;
}

static int compareGSTVALUE(void /*GSTVALUE*/ *a, void /*GSTVALUE*/ *b) {
	GSTVALUE *gstvala = a;
	GSTVALUE *gstvalb = b;
	return gstvala->comparator(gstvala->value, gstvalb->value);
}

static void freeGSTVALUE(void /*GSTVALUE*/ *v) {
	GSTVALUE *gstval = v;
	if(gstval->release != NULL) {
		gstval->release(gstval->value);
	}
	free(gstval);
	return;
}

static GSTVALUE *newGSTVALUE(void *value, void (*d)(void *, FILE *), int (*c)(void *, void *), void (*f)(void *)) {
	GSTVALUE *gstval = malloc(sizeof(GSTVALUE));
	assert(gstval != NULL);
	gstval->value = value;
	setGSTVALUEfrequency(gstval, 1);
	gstval->display = d;
	gstval->comparator = c;
	gstval->release = f;
	return gstval;
}

static int frequencyGSTVALUE(GSTVALUE *gstval) {
	return gstval->frequency;
}

static void setGSTVALUEfrequency(GSTVALUE *gstval, int freq) {
	gstval->frequency = freq;
	return;
}

static void *valueGSTVALUE(GSTVALUE *gstval) {
	return gstval->value;
}

static BSTNODE *findGSTNODE(GST *tree, void *value) {
	GSTVALUE *compareTo = newGSTVALUE(value, tree->display, tree->comparator, NULL);
	BSTNODE *result = findBST(tree->bst, compareTo);
	free(compareTo);
	assert(result == NULL || tree->comparator(valueGSTVALUE(getBSTNODEvalue(result)), value) == 0);
	return result;
}
