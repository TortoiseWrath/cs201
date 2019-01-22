#include "avl.h"
#include "vertex.h"
#include "edge.h"
#include "binomial.h"
#include "scanner.h"
#include "integer.h"
#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// options
int useGST = 0;

static int processOptions(int, char **);
static void giveExplanation();
static void skipWhitespace(FILE *fp);
static void updateVERTEX(void *, void*);
static void sortDLL(DLL *, int (*)(void *, void *));
static int compareVERTEXnumbers(void *, void *);

int main(int argc, char **argv) {
	int argIndex = processOptions(argc, argv);

	AVL *edges = newAVL(displayEDGE, compareEDGE, freeEDGE);
	AVL *vertices = newAVL(displayVERTEX, compareVERTEX, freeVERTEX);
	VERTEX *source = NULL;
	BINOMIAL *heap = newBINOMIAL(displayVERTEX, compareVERTEX, updateVERTEX, NULL);
	DLL *vertexList = newDLL(displayVERTEX, NULL);

	FILE *graph = fopen(argv[argIndex], "r");
	skipWhitespace(graph);

	while(!feof(graph)) {
		int vertex1;
		int vertex2;
		int weight = 1;

		// read vertex1
		skipWhitespace(graph);
		assert(!feof(graph));
		vertex1 = readInt(graph);

		// read vertex2
		skipWhitespace(graph);
		assert(!feof(graph));
		vertex2 = readInt(graph);

		// read weight
		skipWhitespace(graph);
		assert(!feof(graph));
		char c = fgetc(graph);
		if(c != ';') {
			ungetc(c, graph);
			weight = readInt(graph);
			skipWhitespace(graph);
			c = fgetc(graph);
			assert(c == ';');
		}

		skipWhitespace(graph);

		// Always use the smaller vertex number as the first vertex on an edge
		int swapped = 0; // so we can keep track of which one originally came first
		if(vertex1 > vertex2) {
			int tempVertex = vertex1;
			vertex1 = vertex2;
			vertex2 = tempVertex;
			swapped = 1;
		}

		EDGE *edge = newEDGE(vertex1, vertex2, weight);

		// ignore the edge if it already exists
		if(findAVL(edges, edge) != NULL) {
			freeEDGE(edge);
			continue;
		}

		insertAVL(edges, edge);
		VERTEX *new1 = newVERTEX(vertex1);
		VERTEX *v1 = findAVL(vertices, new1);
		if(v1 == NULL) {
			v1 = new1;
			setVERTEXowner(v1, insertBINOMIAL(heap, v1));
			setVERTEXpred(v1, NULL);
			insertAVL(vertices, v1);
			insertDLL(vertexList, 0, v1);
		}
		else {
			freeVERTEX(new1);
		}
		VERTEX *new2 = newVERTEX(vertex2);
		VERTEX *v2 = findAVL(vertices, new2);
		if(v2 == NULL) {
			v2 = new2;
			setVERTEXowner(v2, insertBINOMIAL(heap, v2));
			setVERTEXpred(v2, NULL);
			insertAVL(vertices, v2);
			insertDLL(vertexList, 0, v2);
		}
		else {
			freeVERTEX(new2);
		}
		insertVERTEXneighbor(v1, v2);
		insertVERTEXneighbor(v2, v1);
		insertVERTEXweight(v1, weight);
		insertVERTEXweight(v2, weight);

		if(source == NULL) {
			source = swapped ? v2 : v1; // whichever originally came first
		}
	}

	fclose(graph);
	// assert(sizeAVL(edges) >= sizeAVL(vertices) - 1);
	if(source == NULL) {
		puts("EMPTY\n");
		exit(0);
	}

	// set key of source to 0
	assert(setVERTEXkey(source, 0) == -1); // INF = -1
	decreaseKeyBINOMIAL(heap, getVERTEXowner(source), source);

	assert(sizeAVL(vertices) == sizeDLL(vertexList));
	assert(sizeAVL(vertices) == sizeBINOMIAL(heap));
	// heap (binomial heap) and vertices (AVL tree) both contain all vertices
	// each vertex's owner is a binomial heap node

	while(sizeBINOMIAL(heap) > 0) {
		VERTEX *x = extractBINOMIAL(heap);
		setVERTEXflag(x, 1); //no longer in heap
		DLL *adj = getVERTEXneighbors(x);
		DLL *weights = getVERTEXweights(x);
		firstDLL(adj);
		firstDLL(weights);
		while(moreDLL(adj)) {
			// for each vertex y such that (x, y) is an edge
			VERTEX *y = currentDLL(adj);
			int w = getINTEGER(currentDLL(weights));
			if(getVERTEXflag(y) != 1 && (getVERTEXkey(y) == -1 || w < getVERTEXkey(y))) {
				setVERTEXkey(y, w);
				setVERTEXpred(y, x);
				// insertVERTEXsuccessor(x, y);
				// Can't do this here because y's parent can still change
				decreaseKeyBINOMIAL(heap, getVERTEXowner(y), y);
			}

			nextDLL(adj);
			nextDLL(weights);
		}
	}

	freeBINOMIAL(heap);

	// Build the successor lists.
	while(sizeDLL(vertexList) > 0) {
		VERTEX *x = removeDLL(vertexList, 0);
		if(getVERTEXpred(x) != NULL) {
			insertVERTEXsuccessor(getVERTEXpred(x), x);
		}
	}
	freeDLL(vertexList);

	// MST is now stored using successors and predecessor in each vertex

	QUEUE *currentLevel = newQUEUE(NULL, NULL);
	QUEUE *nextLevel = newQUEUE(NULL, NULL);
	DLL *toDisplay = newDLL(NULL, NULL);

	enqueue(currentLevel, source);
	int level = 0;
	int beginningOfLevel = 1;
	int totalWeight = 0;
	while(sizeQUEUE(currentLevel) > 0) {
		VERTEX *current = dequeue(currentLevel);
		if(beginningOfLevel) {
			printf("%i:", level);
			beginningOfLevel = 0;
		}
		insertDLL(toDisplay, 0, current); // to display later
		DLL *succ = getVERTEXsuccessors(current);
		firstDLL(succ);
		while(moreDLL(succ)) {
			enqueue(nextLevel, currentDLL(succ));
			nextDLL(succ);
		}
		if(sizeQUEUE(currentLevel) == 0) {
			freeQUEUE(currentLevel);
			currentLevel = nextLevel;
			nextLevel = newQUEUE(NULL, NULL);

			// Sort and display the entries from this level.
			sortDLL(toDisplay, compareVERTEXnumbers);
			firstDLL(toDisplay);
			while(moreDLL(toDisplay)) {
				current = currentDLL(toDisplay);
				printf(" %i", getVERTEXnumber(current));
				if(current != source) {
					printf("(%i)%i", getVERTEXnumber(getVERTEXpred(current)), getVERTEXkey(current));
					totalWeight += getVERTEXkey(current);
				}
				nextDLL(toDisplay);
			}
			removeDLLall(toDisplay);

			putc('\n', stdout);
			beginningOfLevel = 1;
			level++;
		}
	}
	freeQUEUE(currentLevel);
	freeQUEUE(nextLevel);
	freeDLL(toDisplay);
	printf("weight: %i\n", totalWeight);


	freeAVL(edges);
	freeAVL(vertices);
	return 0;
}


static void skipWhitespace(FILE *fp) {
	char c;
	//read until next non-whitespace character
	while((c = fgetc(fp)) != EOF && isspace(c)) {
		continue;
	}
	ungetc(c, fp);
	return;
}


// adapted from Dr. Lusth's options.c
static int processOptions(int argc, char **argv) {
    int argIndex;
    int argUsed;
    int separateArg;
    // char *arg;

    argIndex = 1;

    while (argIndex < argc && *argv[argIndex] == '-') {
        /* check if stdin, represented by "-" is an argument */
        /* if so, the end of options has been reached */
        if (argv[argIndex][1] == '\0') return argIndex;

        separateArg = 0;
        argUsed = 0;

        if (argv[argIndex][2] == '\0') {
            // arg = argv[argIndex+1];
            separateArg = 1;
        }
        else {
            // arg = argv[argIndex]+2;
		}

        switch (argv[argIndex][1]) {
            /*
             * when option has an argument, do this
             *
             *     examples are -m4096 or -m 4096
             *
             *     case 'm':
             *         MemorySize = atol(arg);
             *         argUsed = 1;
             *         break;
             *
             *
             * when option does not have an argument, do this
             *
             *     example is -a
             *
             *     case 'a':
             *         PrintActions = 1;
             *         break;
             */

            case 'v':
                giveExplanation();
                break;
            default:
				fprintf(stderr,"option %s not understood\n",argv[argIndex]);
				exit(-1);
        }

        if (separateArg && argUsed)
            ++argIndex;

        ++argIndex;
    }

    return argIndex;
}

static void giveExplanation() {
	fputs("Sean Gillen\n", stdout);
	exit(0);
}

static void updateVERTEX(void *v, void *n) {
	// v is a vertex, n is a binomial heap node
	setVERTEXowner(v, n);
}

static int compareVERTEXnumbers(void *a, void *b) {
	return getVERTEXnumber(a) - getVERTEXnumber(b);
}

static void sortDLL(DLL *list, int (*compare)(void *, void *)) {
	BINOMIAL *heap = newBINOMIAL(NULL, compare, NULL, NULL);
	while(sizeDLL(list) > 0) {
		insertBINOMIAL(heap, removeDLL(list, 0));
	}
	while(sizeBINOMIAL(heap) > 0) {
		insertDLL(list, sizeDLL(list), extractBINOMIAL(heap));
	}
	freeBINOMIAL(heap);
}
