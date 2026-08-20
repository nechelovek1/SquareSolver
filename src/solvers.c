#include <math.h>
#include <assert.h>
#include "solvers.h"
#include "errors.h"

#define EPS 1e-7

RootsCnt squareSolver(double a, double b, double c, double * x1, double * x2)
{
    double ar[3];
    ar[0] = a;
    ar[1] = b;
    ar[2] = c;
    for (int i = 0; i < 3; i ++){
        if (assertMessage(!isinf(ar[i]), "Error: one of arguments is inf")) {
            return ERR_ROOTS;
        }
        if (assertMessage(!isnan(ar[i]), "Error: one of arguments is NaN")) {
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
        return linearSolver(b, c, x1);
    } else {
        double discr = b * b - 4 * a * c;
        if (discr < 0) {
            return ZERO_ROOTS;
        } else if (fequal(discr, 0, EPS)) {
            *x1 = *x2 = -b / (2 * a);
            return ONE_ROOTS;
        } else {
            *x1 = (-b - sqrt(discr)) / (2 * a);
            *x2 = (-b + sqrt(discr)) / (2 * a);
            return TWO_ROOTS;
        }
    }
}

RootsCnt linearSolver(double a, double b, double * x)
{
    if (assertMessage(!isinf(a), "Error: a is inf")) {
        return ERR_ROOTS;
    }
    if (assertMessage(!isinf(b), "Error: b is inf")) {
        return ERR_ROOTS;
    }

    if (assertMessage(!isnan(a), "Error: a is NaN")) {
        return ERR_ROOTS;
    }
    if (assertMessage(!isnan(b), "Error: b is NaN")) {
        return ERR_ROOTS;
    }

    if (assertMessage(x != NULL, "Error: x pointer is NULL")) {
        return ERR_ROOTS;
    }

    if (fequal(a, 0, EPS)) {
        if (fequal(b, 0, EPS)) {
            return INF_ROOTS;
        } else {
            return ZERO_ROOTS;
        }
    } else {
        *x = -b/a;
        return ONE_ROOTS;
    }
}

int fequal(double x, double val, double eps)
{
    return fabs(x - val) < eps;
}