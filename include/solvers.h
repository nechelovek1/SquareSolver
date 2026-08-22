#ifndef SOLVERS_H
#define SOLVERS_H

#include <stdbool.h>
#include <complex.h>


typedef enum {
    ZERO_ROOTS, 
    ONE_ROOTS, 
    TWO_ROOTS, 
    INF_ROOTS,
    ERR_ROOTS
} RootsCnt;


RootsCnt solveSquare(double a, double b, double c, double* x1, double* x2);
RootsCnt solveLinear(double a, double b, double* x);
RootsCnt solveSquareComplex(_Complex double a, _Complex double b, _Complex double c, _Complex double* x1, _Complex double* x2);
RootsCnt solveLinearComplex(_Complex double a, _Complex double b, _Complex double* x);
bool isequalComplex(_Complex double c1, _Complex double c2, double eps);
bool isequal(double v1, double v2, double eps);

#endif