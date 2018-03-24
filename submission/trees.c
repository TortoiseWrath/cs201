#include "avl.h"
#include "gst.h"
#include "scanner.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include "string.h"

// options
int useGST = 0;

static int processOptions(int, char **);
static void giveExplanation();
static char *readStringOrToken(FILE *fp);
static void skipWhitespace(FILE *fp);
static void processGST(char *corpus, char *commands);
static void processAVL(char *corpus, char *commands);
static STRING *readWord(FILE *fp);
static void frequencyGST(GST *, STRING *);
static void frequencyAVL(AVL *, STRING *);
static void insertNonEmptyGST(GST *, STRING *);
static void *deleteNonEmptyGST(GST *, STRING *);
static void insertNonEmptyAVL(AVL *, STRING *);
static void *deleteNonEmptyAVL(AVL *, STRING *);
static int nonempty(STRING *);
static void freeScannedString(void *);

int main(int argc, char **argv) {
	int argIndex = processOptions(argc, argv);

	if(useGST) {
		processGST(argv[argIndex], argv[argIndex + 1]);
	}
	else {
		processAVL(argv[argIndex], argv[argIndex + 1]);
	}

	return -1; // should not get here
}

static void processGST(char *corpus, char *commands) {
	GST *tree = newGST(displaySTRING, compareSTRING, freeScannedString);

	FILE *fp = fopen(corpus, "r");
	skipWhitespace(fp);
	while(!feof(fp)) {
		insertNonEmptyGST(tree, readWord(fp));
		skipWhitespace(fp);
	}
	fclose(fp);

	// read commands into tree
	fp = fopen(commands, "r");
	while(!feof(fp)) {
		STRING *word = readWord(fp);
		char* command = getSTRING(word);
		STRING *deleted = NULL;
		switch (command[0]) {
			case 'i':
				insertNonEmptyGST(tree, readWord(fp));
				break;
			case 'd':
				freeScannedString(word);
				word = readWord(fp);
				deleted = deleteNonEmptyGST(tree, word);
				break;
			case 'f':
				frequencyGST(tree, readWord(fp));
				break;
			case 's':
				displayGST(tree, stdout);
				break;
			case 'r':
				statisticsGST(tree, stdout);
				break;
			default:
				fprintf(stderr, "command %s not understood\n", command);
				freeGST(tree);
				exit(-1);
		}
		if(deleted != NULL) {
			freeScannedString(deleted);
		}
		freeScannedString(word);
		skipWhitespace(fp);
	}
	fclose(fp);

	freeGST(tree);
	exit(0); // done
}

static void processAVL(char *corpus, char *commands) {
	AVL *tree = newAVL(displaySTRING, compareSTRING, freeScannedString);

	FILE *fp = fopen(corpus, "r");
	skipWhitespace(fp);
	while(!feof(fp)) {
		insertNonEmptyAVL(tree, readWord(fp));
		skipWhitespace(fp);
	}
	fclose(fp);

	// read commands into tree
	fp = fopen(commands, "r");
	skipWhitespace(fp);
	while(!feof(fp)) {
		STRING *word = readWord(fp);
		char* command = getSTRING(word);
		STRING *deleted = NULL;
		switch (command[0]) {
			case 'i':
				insertNonEmptyAVL(tree, readWord(fp));
				break;
			case 'd':
				freeScannedString(word);
				word = readWord(fp);
				deleted = deleteNonEmptyAVL(tree, word);
				break;
			case 'f':
				frequencyAVL(tree, readWord(fp));
				break;
			case 's':
				displayAVL(tree, stdout);
				break;
			case 'r':
				statisticsAVL(tree, stdout);
				break;
			default:
				fprintf(stderr, "command %s not understood\n", command);
				freeAVL(tree);
				exit(-1);
		}
		if(deleted != NULL) {
			freeScannedString(deleted);
		}
		freeScannedString(word);
		skipWhitespace(fp);
	}
	fclose(fp);

	freeAVL(tree);
	exit(0); // done
}

static void frequencyGST(GST *tree, STRING *word) {
	printf("Frequency of %s: %i\n", getSTRING(word), findGSTcount(tree, word));
	freeScannedString(word);
}

static void frequencyAVL(AVL *tree, STRING *word) {
	printf("Frequency of %s: %i\n", getSTRING(word), findAVLcount(tree, word));
	freeScannedString(word);
}

static void insertNonEmptyGST(GST *tree, STRING *word) {
	if(nonempty(word)) {
		if(findGST(tree, word) == NULL) {
			insertGST(tree, word);
		}
		else {
			insertGST(tree, word);
			freeScannedString(word);
		}
	}
	else freeScannedString(word);
}

static void insertNonEmptyAVL(AVL *tree, STRING *word) {
	if(nonempty(word)) {
		if(findAVL(tree, word) == NULL) {
			insertAVL(tree, word);
		}
		else {
			insertAVL(tree, word);
			freeScannedString(word);
		}
	}
	else freeScannedString(word);
}

static void *deleteNonEmptyGST(GST *tree, STRING *word) {
	if(nonempty(word)) return deleteGST(tree, word);
	return NULL;
}

static void *deleteNonEmptyAVL(AVL *tree, STRING *word) {
	if(nonempty(word)) return deleteAVL(tree, word);
	return NULL;
}

static int nonempty(STRING *str) {
	return strlen(getSTRING(str));
}

static STRING *readWord(FILE *fp) {
	char *token = readStringOrToken(fp);
	int a = 0;
	int b = 0;
	int ignoreSpace = 1; //start out ignoring whitespace
	int lastAlpha = -1;
	while(token[a] != '\0') {
		if(token[a] == 32 && !ignoreSpace) {
			token[b] = 32;
			b++;
		}
		else if(97 <= token[a] && token[a] <= 122) {
			// [a-z]
			token[b] = token[a];
			lastAlpha = b;
			ignoreSpace = 0; // stop ignoring spaces
			b++;
		}
		else if(65 <= token[a] && token[a] <= 90) {
			// [A-Z]
			token[b] = token[a] + 32; // convert to lowercase
			lastAlpha = b;
			ignoreSpace = 0;
			b++;
		}
		a++;
	}
	token[lastAlpha + 1] = '\0'; // end of cleaned string
	return newSTRING(token);
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
			case 'g':
				useGST = 1;
				break;
            case 'r':
				// do nothing special
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

static char *readStringOrToken(FILE *fp) {
	skipWhitespace(fp);
	if(feof(fp)) return "";
	char c = fgetc(fp);
	if(c == '"') { // it is a double quoted string
		ungetc('"', fp);
		return readString(fp);
	}
	else { // it is a token
		ungetc(c, fp);
		return readToken(fp);
	}
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

static void freeScannedString(void *s) {
	free(getSTRING(s));
	freeSTRING(s);
	return;
}
