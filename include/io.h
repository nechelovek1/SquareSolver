/*!
    \file
    \brief Библиотека ввода-вывода
*/
#ifndef IO_H
#define IO_H

#include <complex.h>

#include "solvers.h"

/*!
    Выводит комплексные корни квадратного уравнения в файл
    \param[in] fp указатель на файл
    \param[in] rootsCnt количество корней
    \param[in] x1 первый корень
    \param[in] x2 второй корень
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функии произошла ошибка
*/
int fPrintRootsComplex(FILE* fp, RootsCnt rootsCnt, _Complex double x1, _Complex double x2);

/*!
    Выводит комплексные корни квадратного уравнения в файл
    \param[in] fp указатель на файл
    \param[in] rootsCnt количество корней
    \param[in] x1 первый корень
    \param[in] x2 второй корень
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функии произошла ошибка
*/

int fPrintRoots(FILE* fp, RootsCnt rootsCnt, double x1, double x2);

/*!
    Выводит квадратное уравнение ax^2+bx+c=0
    \param[in] fp указатель на файл
    \param[in] a старгий коэффициент
    \param[in] b средний коэффициент
    \param[in] c свободный коэффициент
    \return 0 - функция выполнилась без ошибок, -1 в результате выполнения функии произошла ошибка


*/
int fPrintEquation(FILE* fp, double a, double b, double c);

/*!
    Очищает входной буфер пока не встретит символ переноса строки
    \param[in] fp указатель на файл
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функии произошла ошибка       
*/
int fClearInputBuffer(FILE* fp);

/*!
    Считывает строку без символа переноса строки
    \param[in] fp указатель на файл
    \param[out] str указатель для сохранения строки
    \param[in] cnt максимальная длина строки (с нулевым символом)
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функии произошла ошибка  
*/
int fGetString(FILE* fp, char* str, unsigned int cnt);

int fPrintComplex(FILE* fp, _Complex double c);
//int fGetComplex(FILE* fp, _Complex double* c);

/*!
    Открывает файл. Если указана пустая строка, использует поток по умолчанию
    \param[in] filename указатель на строку имения файла
    \param[in] mode указатель на строку режима для открытия файла
    \param[in] def указатель на файл, используемый по умолчанию
    \return указатель на файл, если функция выполнилась успешно, NULL - при выполнении функции произошла ошибка 
*/
FILE * fOpenDefault(const char* filename, const char* mode, FILE* def);

#endif