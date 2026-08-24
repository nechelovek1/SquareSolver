#ifndef IO_H
#define IO_H

#include <complex.h>

#include "solvers.h"

/*
    Выводит комплексные корни квадратного уравнения в файл.
    Аргументы:
        FILE* fp                   - указатель на файл
        RootsCnt rootsCnt          - количество корней
        _Complex double x1         - первый корень
        _Complex double x2         - второй корень
    Возващаемое значение:
        0  - функция выполнилась без ошибок
        -1 - в результате выполнения функии возникла ошибка
*/
int fPrintRootsComplex(FILE* fp, RootsCnt rootsCnt, _Complex double x1, _Complex double x2);

/*
    Выводит корни квадратного уравнения в файл.
    Аргументы:
        FILE* fp          - указатель на файл
        RootsCnt rootsCnt - количество корней
        double x1         - первый корень
        double x2         - второй корень
    Возвращаемое значение:
        0  - функция выполнилась без ошибок
        -1 - в результате выполнения функии возникла ошибка
*/
int fPrintRoots(FILE* fp, RootsCnt rootsCnt, double x1, double x2);

/*
    Выводит квадратное уравнение ax^2+bx+c=0.
    Аргументы:
        FILE* fp - указатель на файл
        double a - старгий коэффициент
        double b - средний коэффициент
        double c - свободный коэффициент
    Возвращаемое значение:
        0  - функция выполнилась без ошибок
        -1 - в результате выполнения функии возникла ошибка


*/
int fPrintEquation(FILE* fp, double a, double b, double c);

int fClearInputBuffer(FILE* fp);
int fGetString(FILE* fp, char * str, int cnt);
int fPrintComplex(FILE* fp, _Complex double c);
int fGetComplex(FILE* fp, _Complex double* c);
FILE * fOpenDefault(const char*, const char*, FILE*);

#endif