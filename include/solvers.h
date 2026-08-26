/*!
    \file
    \brief Библиотека для решения квадратных и линейных уравнений
*/
#ifndef SOLVERS_H
#define SOLVERS_H

#include <stdbool.h>
#include <complex.h>

/*!
    \brief погрешность
*/
const double EPS = 1e-7;

/*!
    \brief Количество корней
    \param ZERO_ROOTS нет корней
    \param ONE_ROOTS один корень
    \param TWO_ROOTS два корня
    \param INF_ROOTS бесконечность корней
    \param ERR_ROOTS ошибка при решении уравнения
*/
typedef enum {
    ZERO_ROOTS,
    ONE_ROOTS,
    TWO_ROOTS,
    INF_ROOTS,
    ERR_ROOTS
} RootsCnt;

/*!
    Решает квадратное уравнение ax^2+bx+c=0 в действительных числах.
    \param[in] a старший коэффициент
    \param[in] b средний коэффициент
    \param[in] c свободный коэффициент
    \param[out] x1 указатель на переменную для сохранения первого корня
    \param[out] x2 указатель на переменную для сохранения второго корня
    \return количество корней RootsCnt  
*/
RootsCnt solveSquare(double a, double b, double c, double* x1, double* x2);

/*!
    Решает линейное уравнение ax+b=0 в действительных числах.
    \param[in] a старший коэффициент
    \param[in] b свободный коэффициент
    \param[out] x указатель на переменную для сохранения корня
    \return количество корней RootsCnt
*/
RootsCnt solveLinear(double a, double b, double* x);

/*!
    Решает квадратное уравнение ax^2+bx+c=0 в комплексных числах.
    \param[in] a старший коэффициент
    \param[in] b средний коэффициент
    \param[in] c свободный коэффициент
    \param[out] x1 указатель на переменную для сохранения первого корня
    \param[out] x2 указатель на переменную для сохранения второго корня
    \return количество корней RootsCnt    
*/
RootsCnt solveSquareComplex(_Complex double a, _Complex double b, _Complex double c, _Complex double* x1, _Complex double* x2);

/*!
    Решает линейное уравнение ax+b=0 комплексных числах.
    \param[in] a старший коэффициент
    \param[in] b свободный коэффициент
    \param[out] x указатель на переменную для сохранения корня
    \return количество корней RootsCnt  
*/
RootsCnt solveLinearComplex(_Complex double a, _Complex double b, _Complex double* x);

/*!
    Сравнивает 2 действительных числа
    \param[in] v1 первое число
    \param[in] v2 второе число
    \param[in] eps погрешность при которой числа можно считать равными
    \return true, если числа можно считать равными в пределах погрешности 

*/
bool isequal(double v1, double v2, double eps);

/*!
    Сравнивает 2 комплексных числа
    \param[in] v1 первое число
    \param[in] v2 второе число
    \param[in] eps погрешность при которой числа можно считать равными
    \return true, если числа можно считать равными в пределах погрешности

*/
bool isequalComplex(_Complex double c1, _Complex double c2, double eps);

#endif