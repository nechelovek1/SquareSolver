#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <complex.h>
#include <stdbool.h>

#define INF_ROOTS 10
#define ZERO_ROOTS 0
#define ONE_ROOTS 1
#define TWO_ROOTS 2

int solveSquareC(_Complex double a, _Complex double b, _Complex double c, _Complex double* x1, _Complex double* x2);
int solveLinearC(_Complex double a, _Complex double b, _Complex double* x);
void plotParabol(double a, double b, double c);
double calcParabol(double a, double b, double c, double x);
bool parseEq(char s[], double* a, double* b, double* c);

int main(int argc, const char * argv[])
{
    sscanf("%lgx^%d");
    /*/plotParabol(1, 2, 1);
    _Complex double arr[3] = {};
    for (int i = 0; i < 3; i ++){
        double im = 0, re = 0;
        scanf("%lf %lf", &re, &im);
        arr[i] = re + im * I;
    }
    _Complex double x1 = 0, x2 = 0;
    solveSquareC(1, 2, 1, &x1, &x2);
    printf("x1=%lf+%lfi\n", creal(x1), cimag(x1));
    printf("x1=%lf+%lfi\n", creal(x2), cimag(x2));
    /*/
    return 0;
}

int solveLinearC(_Complex double a, _Complex double b, _Complex double* x)
{
    assert(!isnan(creal(a)));
    assert(!isnan(cimag(a)));

    assert(!isnan(creal(b)));
    assert(!isnan(cimag(b)));

    assert(x != NULL);

    if (cabs(a) == 0) {
        if (cabs(b) == 0) {
            return INF_ROOTS;
        } else {
            return ZERO_ROOTS;
        }
    }

    *x = -b / a;

    return ONE_ROOTS;
}

int solveSquareC(_Complex double a, _Complex double b, _Complex double c, _Complex double* x1, _Complex double* x2)
{
    assert(!isnan(creal(a)));
    assert(!isnan(cimag(a)));

    assert(!isnan(creal(b)));
    assert(!isnan(cimag(b)));
    
    assert(!isnan(creal(c)));
    assert(!isnan(cimag(c)));

    assert(x1 != NULL);
    assert(x2 != NULL);

    assert(x1 != x2);

    if (cabs(a) == 0) {
        return solveLinearC(b, c, x1);
    }

    _Complex double d = b * b - 4 * a * c;
    *x1 = (-b - csqrt(d)) / (2 * a);
    *x2 = (-b + csqrt(d)) / (2 * a);
    
    return TWO_ROOTS;
}

double calcParabol(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}
void plotParabol(double a, double b, double c)
{   
    int screensize = 40;
    char screen[screensize][screensize];
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            screen[i][j] = ' ';
        }
    }

    for (int i = 0; i < 40; i++) {
        screen[i][20] = '|';
        screen[20][i] = '_';
    }

    for (int i = -20; i < 20; i++) {
        double yr = calcParabol(a, b, c, i);
        double yl = calcParabol(a, b, c, i + 1);
        double ym = (yr + yl) / 2;
        int j = (int) ym;
        if (j >= -20 && j < 20){
            screen[-j + 20][i + 20] = '*';
        }
    }

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            putchar(screen[i][j]);
        }
        putchar('\n');
    }
}

double parseEq(char s[], double* a, double* b, double* c)
{
    int len = strlen(s);
    for (int i = 0; i < len; i++) {

    }
}

bool parseEq(char s[], int coefs[])
{
    size_t len = strlen(s);
    double coef = 0.0;
    int numStartIdx = 0;
    for (int i = 0; i < len; i++) {
        if (tolower(s[i]) == 'x' && s[i + 1] == ) {

        }
    }
}
