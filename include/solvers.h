#ifndef SOLVERS_H
#define SOLVERS_H

#include <stdbool.h>

typedef enum {
    ZERO_ROOTS, 
    ONE_ROOTS, 
    TWO_ROOTS, 
    INF_ROOTS,
    ERR_ROOTS
} RootsCnt;

RootsCnt solveSquare(double, double, double, double *, double *);
RootsCnt solveLinear(double, double, double *);
bool fequal(double, double, double);
bool assertMessage(int, const char []);

#endif