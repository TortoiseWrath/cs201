#include "avl.h"
#include "bst.h"

struct avl {
	BST *bst
};

typedef struct avlval AVLvalue;
struct avlval {
	void *value,
	int frequency
};

static void swapper(BSTNODE *, BSTNODE *);

AVL *newAVL(void (*)(void *, FILE *) d, int (*)(void *, void *) c, void (*)(void *) f) {
	AVL *tree = malloc(sizeof(AVL));
	assert(tree != NULL);
	tree->bst = newBST(d, c, swapper, f);
}
void insertAVL(AVL *,void *);
int findAVLcount(AVL *,void *);
void *findAVL(AVL *,void *);
void *deleteAVL(AVL *,void *);
int sizeAVL(AVL *);
int duplicatesAVL(AVL *);
void statisticsAVL(AVL *,FILE *);
void displayAVL(AVL *,FILE *);
void displayAVLdebug(AVL *,FILE *);
void freeAVL(AVL *);

static void swapper(BSTNODE *a, BSTNODE *b) {
	void *temp = getBSTNODEvalue(a);
	setBSTNODEvalue(a, getBSTNODEvalue(b));
	setBSTNODEvalue(b, temp);
	return;
}
