#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <complex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "errors.h"
#include "parser.h"
#include "tests.h"
#include "solvers.h"

const int MAX_STR_LEN = 100;

void plotParabol(double a, double b, double c);
double calcParabol(double a, double b, double c, double x);

int solvePolynom(double* coefs, unsigned int coefsCnt, double* roots);
int calculateDerrivativePolynom(double* coefs, unsigned int coefsCnt, double* coefsDerr);
double findRootBinarySearch(double* coefs, unsigned int coefsCnt, double l, double r, double eps);
double calcPolynom(const double coefs[], unsigned int coefsCnt, double x);


int main(int argc, const char* argv[])
{
    const char* tests[] = {
        "x^2+x+3+4x+5=0",
        "2.3x-3+4x^2=x-x+6",
        "0=0",
        "x=x",
        "lksdhlksdahflsa",
        "+xxxx=-xxxxx",
        "2.3x-3+4x^2.1=x-x+6"
    };

    unsigned int len = sizeof(tests) / sizeof(tests[0]);

    for (unsigned int i = 0; i < len; i++)
    {
        printf("%u\n", i);
        const unsigned int coefCnt = 3;
        double coefs[coefCnt] = {};
        parseEqation(tests[i], strlen(tests[i]), coefs, coefCnt);
        printf("%s\n", tests[i]);
        printf("%lg %lg %lg\n", coefs[0], coefs[1], coefs[2]);
    }

    runTestsSquare(10000000);
    
    return 0;
}   



double calcParabol(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

void plotParabol(double a, double b, double c)
{   
    const int screensize = 40;
    char screen[screensize][screensize];
    for (int i = 0; i < screensize; i++) 
    {
        for (int j = 0; j < screensize; j++) 
        {
            screen[i][j] = ' ';
        }
    }

    for (int i = 0; i < screensize; i++) 
    {
        screen[i][screensize / 2] = '|';
        screen[screensize / 2][i] = '_';
    }

    for (int i = -screensize / 2; i < screensize / 2; i++) 
    {
        double yr = calcParabol(a, b, c, i);
        double yl = calcParabol(a, b, c, i + 1);
        double ym = (yr + yl) / 2;
        int j = (int) ym;
        if (j >= -screensize / 2 && j < screensize / 2) {
            screen[-j + screensize / 2][i + screensize / 2] = '*';
        }
    }

    for (int i = 0; i < screensize; i++) 
    {
        for (int j = 0; j < screensize; j++) 
        {
            putchar(screen[i][j]);
        }
        putchar('\n');
    }
}

int solvePolynom(double* coefs, unsigned int coefsCnt, double* roots)
{
    const double eps = 1e-6;

    if (coefsCnt > 2) {
        double* coefsDerr = calloc(coefsCnt - 1, sizeof(double));
        if (coefsDerr == NULL) {
            return -1;
        }
        calculateDerrivativePolynom(coefs, coefsCnt, coefsDerr);

        double* rootsDerr = calloc(coefsCnt - 1, sizeof(double));
        if (rootsDerr == NULL) {
            return -1;
        }

        int rootsDerrCnt = solvePolynom(coefsDerr, coefsCnt - 1, rootsDerr);

        if (rootsDerrCnt == 0) {
            if (coefsDerr < 0) {
                roots[0] = findRootBinarySearch(coefs, coefsCnt, DBL_MAX, DBL_MIN, eps);
            } else {
                roots[0] = findRootBinarySearch(coefs, coefsCnt, DBL_MIN, DBL_MAX, eps);
            }

            for (unsigned int i = 0; i < rootsDerrCnt; i++) 
            {
                roots[i] = NAN;
            }

            return 1;
        } else {

        }

        //if (calcPolynom(coefsDerr, coefsCnt - 1, )) {
        //
        //}

        for (unsigned int i = 1; i < coefsCnt - 1; i++)
        {

        }
    } else {
        
    }
} 

int calculateDerrivativePolynom(double* coefs, unsigned int coefsCnt, double* coefsDerr)
{
    if (coefs == NULL || coefsDerr == NULL) {
        return -1;
    }

    for (unsigned int i = 1; i < coefsCnt; i++)
    {
        coefsDerr[i - 1] = coefs[i] * i;
    }

    return 0;
}

double findRootBinarySearch(double* coefs, unsigned int coefsCnt, double l, double r, double eps)
{
    double root = (l + r) / 2;
    double y = calcPolynom(coefs, coefsCnt, root);

    while (!isequal(y, 0, eps))
    {
        if (y < 0) {
            l = root;
        } else {
            r = root;
        }

        root = (l + r) / 2;
        y = calcPolynom(coefs, coefsCnt, root);
    }

    return root;
}

double calcPolynom(const double coefs[], unsigned int coefsCnt, double x)
{
    double y = 0; double xCur = 1;

    for (unsigned int i = 0; i < coefsCnt; i++)
    {
        y += coefs[i] * xCur;
        xCur *= x;
    }

    return y;
}