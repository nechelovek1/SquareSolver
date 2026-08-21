#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <complex.h>
#include <stdbool.h>

#include "solvers.h"

const double EPS = 1e-10;

bool assertMessage(int n, const char s[])
{
    if (!n) {
        fprintf(stderr, "%s\n", s);
        return true;
    } else {
        return false;
    }
}

RootsCnt solveSquare(double a, double b, double c, double * x1, double * x2)
{
    double arr[3] = {a, b, c};

    for (int i = 0; i < 3; i ++) {
        if (assertMessage(!isinf(arr[i]), "Error: one of arguments is inf")) {
            return ERR_ROOTS;
        }
        if (assertMessage(!isnan(arr[i]), "Error: one of arguments is NaN")) {
            return ERR_ROOTS;
        }
    }

    if (assertMessage(x1 != NULL, "Error: x1 pointer is NULL")) {
        return ERR_ROOTS;
    }
    if (assertMessage(x2 != NULL, "Error: x2 pointer is NULL")) {
        return ERR_ROOTS;
    }

    if (assertMessage(x1 != x2, "Error: pointers collision")) {
        return ERR_ROOTS;
    }

    if (fequal(a, 0, EPS)) {
        return solveLinear(b, c, x1);
    } else {
        double discr = b * b - 4 * a * c;
        if (fequal(discr, 0, EPS)) {
            *x1 = *x2 = -b / (2 * a);
            return ONE_ROOTS;
        } else if (discr < 0) {
            return ZERO_ROOTS;
        } else {
            *x1 = (-b - sqrt(discr)) / (2 * a);
            *x2 = (-b + sqrt(discr)) / (2 * a);
            return TWO_ROOTS;
        }
    }
}


RootsCnt solveLinear(double a, double b, double* x)
{
    double arr[2] = {a, b}; // arr

    for (int i = 0; i < 2; i ++) {
        if (assertMessage(!isinf(arr[i]), "Error: one of arguments is inf")) {
            return ERR_ROOTS;
        }
        if (assertMessage(!isnan(arr[i]), "Error: one of arguments is NaN")) {
            return ERR_ROOTS;
        }
    }

    if (assertMessage(x != NULL, "Error: x pointer is NULL")) {
        return ERR_ROOTS;
    }

    if (fequal(a, 0.0, EPS)) {
        if (fequal(b, 0.0, EPS)) {
            return INF_ROOTS;
        } else {
            return ZERO_ROOTS;
        }
    } else {
        *x = -b / a;
        return ONE_ROOTS;
    }
}

bool fequal(double x, double val, double eps)
{
    return fabs(x - val) < eps;
}
