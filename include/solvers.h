#ifndef SOLVERS_H
#define SOLVERS_H

typedef enum{
    ZERO_ROOTS, 
    ONE_ROOTS, 
    TWO_ROOTS, 
    INF_ROOTS,
    ERR_ROOTS
} RootsCnt;

RootsCnt squareSolver(double, double, double, double *, double *);
RootsCnt linearSolver(double, double, double *);
int fequal(double, double, double);

#endif