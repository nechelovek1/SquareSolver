#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <complex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "errors.h"
#include "parser.h"
#include "tests.h"

const int MAX_STR_LEN = 100;

void plotParabol(double a, double b, double c);
double calcParabol(double a, double b, double c, double x);


int main(int argc, const char* argv[])
{
    runTestsParser();
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
