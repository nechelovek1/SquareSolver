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
        -1 - в результате выполнения функии произошла ошибка
*/
int fPrintRootsComplex(FILE* fp, RootsCnt rootsCnt, _Complex double x1, _Complex double x2);

/*
    Выводит комплексные корни квадратного уравнения в файл.
    Аргументы:
        FILE* fp          - указатель на файл
        RootsCnt rootsCnt - количество корней
        _Complex double x1         - первый корень
        _Complex double x2         - второй корень
    Возвращаемое значение:
        0  - функция выполнилась без ошибок
        -1 - в результате выполнения функии произошла ошибка
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
        -1 - в результате выполнения функии произошла ошибка


*/
int fPrintEquation(FILE* fp, double a, double b, double c);

/*
    Очищает входной буфер пока не встретит символ переноса строки
    Аргументы:
        FILE* fp - указатель на файл
    Возвращаемое значение:
        0  - функция выполнилась без ошибок
        -1 - в результате выполнения функии произошла ошибка       
*/
int fClearInputBuffer(FILE* fp);

/*
    Считывает строку без символа переноса строки
    Аргументы:
        FILE* fp         - указатель на файл
        char* str        - указатель для сохранения строки
        unsigned int cnt - максимальная длина строки (с нулевым символом)
    Возвращаемое значение:
        0  - функция выполнилась без ошибок
        -1 - в результате выполнения функии произошла ошибка  
*/
int fGetString(FILE* fp, char* str, unsigned int cnt);

int fPrintComplex(FILE* fp, _Complex double c);
int fGetComplex(FILE* fp, _Complex double* c);

/*
    Открывает файл.
    Аргументы:
        const char* filename - указатель на строку имения файла
        const char* mode - указатель на строку режима для открытия файла
        FILE* def -указатель на файл, используемый по умолчанию
    Возвращаемое значение:
        FILE* - указатель на файл, если функция выполнилась успешно
              - NULL, если при выполнении функции произошла ошибка 
*/
FILE * fOpenDefault(const char* filename, const char* mode, FILE* def);

#endif