#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

FILE *OpenFile(char *fileName,char *mode);
void Fatal(char *,...);

int Successes = 0;
int Trials = 0;

int
main(int argc,char **argv)
    {
    if (argc != 2) Fatal("usage: %s SUBMISSION_NUMBER\n",argv[0]);

    int submission = atoi(argv[1]);

    printf("TESTING COMPLETE.\n");
    printf("\n");

    FILE *fp = fopen("BONUS","r");
    if (fp != 0)
        {
        fscanf(fp,"%d",&Successes);
        fscanf(fp,"%d",&Trials);
        fclose(fp);
        }

    double bonus = Trials == 0? 0 : Successes * 5.0 / Trials;

    if (submission == 0)
        {
        printf("Your bonus will be %.2f points.\n",bonus);
        printf("\n");
        }
    else
        {
        FILE *fp = fopen("TRIALS","r");
        if (fp != 0)
            {
            fscanf(fp,"%d",&Successes);
            fscanf(fp,"%d",&Trials);
            fclose(fp);
            }
        printf("Your bonus is %.2f points.\n",bonus);
        printf("\n");
        }

    printf("Tests passed: %d\n",Successes);
    printf("Tests failed: %d\n",Trials - Successes);
    printf("\n");

    if (Trials != Successes && submission < 4)
        printf("There are test failures, you need to resubmit.\n");
    else if (Trials != Successes)
        {
        printf("There are test failures.\n");
        printf("No more submissions are allowed.\n");
        printf("Overall Score: %.2f\n",bonus);
        }
    else
        {
        printf("All tests passed.\n");
        printf("Overall Score: %.2f/100\n",100 - 10*submission + bonus);
        }

    return 0;
    }

void
Fatal(char *fmt, ...)
    {
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
    }

/* only -oXXX  or -o XXX options */


FILE *
OpenFile(char *fileName,char *mode)
    {
    FILE *fp;

    if ((fp = fopen(fileName, mode)) == 0)
        {
        char *s;
        switch (*mode)
           {
           case 'w':
               s = "writing";
               break;
           case 'r':
               s = "reading";
               break;
           case 'a':
               s = "appending";
               break;
           default:
               s = 0;
               break;
           }
        if (s)
            Fatal("file %s could not be opened for %s\n", fileName, s);
        else
            Fatal("file %s could not be opened mode %s\n", fileName, mode);
        }

    return fp;
    }
