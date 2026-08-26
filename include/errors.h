#ifndef ERRORS_H
#define ERRORS_H

#include <stdbool.h>
#include <complex.h>

bool assertMessage(bool expressionResult, const char message[]);
/*
    Выводит в поток ошибок сообщение если логическое выражение ложно
    Аргументы:
        bool l               - логическое выражение
        const char message[] - сообщение
    Возвращаемое значение:
        bool
*/

bool assertInfNaN(double a);
/*
    Выводит в поток ошибок сообщение если действительное число является inf или nan
    Аргументы:
        double a - действительное число
    Возвращаемое значение:
        bool
*/

bool assertInfNaNComplex(_Complex double c);
/*
    Выводит в поток ошибок сообщение если комплексное число является inf или nan
    Аргументы:
        _Complex double a - комплексное число
    Возвращаемое значение:
        bool
*/

#endif