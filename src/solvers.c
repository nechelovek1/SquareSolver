#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <complex.h>
#include <stdbool.h>

#include "solvers.h"
#include "errors.h"

RootsCnt solveSquare(double a, double b, double c, double* x1, double* x2)
{
    const unsigned int coefsCnt = 3;
    double coefs[coefsCnt] = {a, b, c};

    for (unsigned int i = 0; i < coefsCnt; i ++) {
        if (assertInfNaN(coefs[i])) {
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

    if (isequal(a, 0, EPS)) {
        return solveLinear(b, c, x1);
    } else {
        double discr = b * b - 4 * a * c;
        if (isequal(discr, 0, EPS)) {
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
    const unsigned int coefsCnt = 2;
    double coefs[coefsCnt] = {a, b};

    for (unsigned int i = 0; i < coefsCnt; i ++) {
        if (assertInfNaN(coefs[i])) {
            return ERR_ROOTS;
        }
    }

    if (assertMessage(x != NULL, "Error: x pointer is NULL")) {
        return ERR_ROOTS;
    }

    if (isequal(a, 0.0, EPS)) {
        if (isequal(b, 0.0, EPS)) {
            return INF_ROOTS;
        } else {
            return ZERO_ROOTS;
        }
    } else {
        *x = -b / a;
        return ONE_ROOTS;
    }
}

RootsCnt solveLinearComplex(_Complex double a, _Complex double b, _Complex double* x)
{
    const unsigned int coefsCnt = 2;
    _Complex double coefs[coefsCnt] = {a, b};
    
    for (unsigned int i = 0; i < coefsCnt; i++) {
        if (assertInfNaNComplex(coefs[i])) {
            return ERR_ROOTS;
        }
    }

    if (assertMessage(x != NULL, "x pointer is NULL")) {
        return ERR_ROOTS;
    }

    if (isequalComplex(a, 0.0, EPS)) {
        if (isequalComplex(b, 0.0, EPS)) {
            return INF_ROOTS;
        } else {
            return ZERO_ROOTS;
        }
    }

    *x = -b / a;

    return ONE_ROOTS;
}

RootsCnt solveSquareComplex(_Complex double a, _Complex double b, _Complex double c, _Complex double* x1, _Complex double* x2)
{
    const unsigned int coefsCnt = 3;
    _Complex double coefs[coefsCnt] = {a, b, c};

    for (unsigned int i = 0; i < coefsCnt; i++) {
        if (assertInfNaNComplex(coefs[i])) {
            return ERR_ROOTS;
        }
    }

    if (assertMessage(x1 != NULL, "x1 pointer is NULL")) {
        return ERR_ROOTS;
    }
    if (assertMessage(x2 != NULL, "x2 pointer is NULL")) {
        return ERR_ROOTS;
    }

    if(assertMessage(x1 != x2, "Pointers collision")) {
        return ERR_ROOTS;
    }

    if (isequalComplex(a, 0.0, EPS)) {
        return solveLinearComplex(b, c, x1);
    }

    _Complex double d = b * b - 4 * a * c;

    if (isequalComplex(d, 0.0, EPS)) {
        *x1 = *x2 = -b / (2 * a);
        return ONE_ROOTS;
    }   
    *x1 = (-b - csqrt(d)) / (2 * a);
    *x2 = (-b + csqrt(d)) / (2 * a);
    
    return TWO_ROOTS;
}


bool isequal(double v1, double v2, double eps)
{
    return fabs(v1 - v2) < eps;
}

bool isequalComplex(_Complex double c1, _Complex double c2, double eps)
{
    return (isequal(creal(c1), creal(c2), eps) && isequal(cimag(c2), cimag(c2), eps));
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