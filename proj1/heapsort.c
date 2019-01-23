#include "heap.h"
#include "scanner.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include "integer.h"
#include "string.h"
#include "real.h"

// options
int sortReals = 0;
int sortStrings = 0;
int sortDecreasing = 0;

static int processOptions(int, char **);
static void giveExplanation();
static int rcompareREAL(void *a, void *b);
static int rcompareSTRING(void *a, void *b);
static int rcompareINTEGER(void *a, void *b);
static char *readStringOrToken(FILE *fp);
static void skipWhitespace(FILE *fp);

int main(int argc, char **argv) {
	int argIndex = processOptions(argc, argv);

	if(sortReals && sortStrings) {
		fputs("Cannot sort both reals and strings.", stderr);
		exit(-1);
	}

	int (*compare)(void *, void *);
	void (*display)(void *, FILE *);
	void (*release)(void *);

	FILE *fp = fopen(argv[argIndex], "r");
	HEAP *h;

	if(sortReals) {
		release = freeREAL;
		display = displayREAL;
		compare = sortDecreasing ? rcompareREAL : compareREAL; // use a max-heap for decreasing to simplify display
		h = newHEAP(display, compare, release);
		while(!feof(fp)) {
			insertHEAP(h, newREAL(readReal(fp)));
			skipWhitespace(fp);
		}
	}
	else if(sortStrings) {
		release = freeSTRING;
		display = displaySTRING;
		compare = sortDecreasing ? rcompareSTRING : compareSTRING;
		h = newHEAP(display, compare, release);
		while(!feof(fp)) {
			insertHEAP(h, newSTRING(readStringOrToken(fp)));
			skipWhitespace(fp);
		}
	}
	else {
		release = freeINTEGER;
		display = displayINTEGER;
		compare = sortDecreasing ? rcompareINTEGER : compareINTEGER;
		h = newHEAP(display, compare, release);
		while(!feof(fp)) {
			insertHEAP(h, newINTEGER(readInt(fp)));
			skipWhitespace(fp);
		}
	}

	fclose(fp);

	buildHEAP(h);

	int firstValue = 1;
	void *value;
	while(sizeHEAP(h) > 0) {
		if(!firstValue) fputc(' ', stdout);
		firstValue = 0;
		value = extractHEAP(h);
		display(value, stdout);
		release(value);
	}

	freeHEAP(h);

	fputc('\n', stdout);
	return 0;
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
			case 'r':
				sortReals = 1;
				break;
			case 's':
				sortStrings = 1;
				break;
			case 'D':
				sortDecreasing = 1;
				break;
            case 'i':
			case 'I':
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
	fputs("Written by Sean Gillen <sdgillen@crimson.ua.edu>\n", stdout);
	fputs("My heapsort takes time O(n lg n) because it consists of:\n", stdout);
	fputs("- an O(n) routine to read the input file into the unheapified heap \n", stdout);
	fputs("- a call to buildHEAP, which calls:\n", stdout);
	fputs("    - peekSTACK (O(1)), getBSTNODEleft (O(1)), and pop (O(1)) each ⌈n/2⌉ times (O(n))\n", stdout);
	fputs("    - heapify (T(n) ≤ T(2n/3) + θ(1) → O(lg n)) ⌊n/2⌋ times (O(n lg n))\n", stdout);
	fputs("    - freeSTACK (O(n))\n", stdout);
	fputs("    - bftraverse (O(n))\n", stdout);
	fputs("- n calls to extractHEAP, each consisting of a constant number of calls to O(1) routines and one call to heapify (O(lg n))\n", stdout);
	fputs("As such, the heapsort routine is O(n lg n + n + n lg n + n + n + cn + n lg n) = O(n lg n).\n", stdout);

	exit(0);
}

static int rcompareREAL(void *a, void *b) {
	return -1 * compareREAL(a, b);
}

static int rcompareINTEGER(void *a, void *b) {
	return -1 * compareINTEGER(a, b);
}

static int rcompareSTRING(void *a, void *b) {
	return -1 * compareSTRING(a, b);
}

static char *readStringOrToken(FILE *fp) {
	skipWhitespace(fp);
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
