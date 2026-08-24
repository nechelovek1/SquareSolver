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

/*
    Решает квадратное уравнение ax^2+bx+c=0 в действительных числах.
    Аргументы:
        double a   - старший коэффициент
        double b   - средний коэффициент
        double c   - свободный коэффициент
        double* x1 - указатель на переменную для сохранения первого корня
        double* x2 - указатель на переменную для сохранения второго корня
    Возвращаемое значение:
        RootsCnt - количество корней       
*/
RootsCnt solveSquare(double a, double b, double c, double* x1, double* x2);

/*
    Решает линейное уравнение ax+b=0 в действительных числах.
    Аргументы:
        double a  - старший коэффициент
        double b  - свободный коэффициент
        double* x - указатель на переменную для сохранения корня
    Возвращаемое значение:
        RootsCnt - количество корней
*/
RootsCnt solveLinear(double a, double b, double* x);

/*
    Решает квадратное уравнение ax^2+bx+c=0 в комплексных числах.
    Аргументы:
        _Complex double a   - старший коэффициент
        _Complex double b   - средний коэффициент
        _Complex double c   - свободный коэффициент
        _Complex double* x1 - указатель на переменную для сохранения первого корня
        _Complex double* x2 - указатель на переменную для сохранения второго корня
    Возвращаемое значение:
        RootsCnt - количество корней       
*/
RootsCnt solveSquareComplex(_Complex double a, _Complex double b, _Complex double c, _Complex double* x1, _Complex double* x2);

/*
    Решает линейное уравнение ax+b=0 комплексных числах.
    Аргументы:
        _Complex double a  - старший коэффициент
        _Complex double b  - свободный коэффициент
        _Complex double* x - указатель на переменную для сохранения корня
    Возвращаемое значение:
        RootsCnt - количество корней    
*/
RootsCnt solveLinearComplex(_Complex double a, _Complex double b, _Complex double* x);

bool isequalComplex(_Complex double c1, _Complex double c2, double eps);
bool isequal(double v1, double v2, double eps);

#endif