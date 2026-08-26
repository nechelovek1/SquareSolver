#ifndef ERRORS_H
#define ERRORS_H

#include <stdbool.h>
#include <complex.h>

/*!
    Выводит в поток ошибок сообщение если логическое выражение ложно
    \param[in] expressionResult логическое выражение
    \param[in] message[] - сообщение
    \return true, если значение ложно, false если значение истинно
*/
bool assertMessage(bool expressionResult, const char message[]);

/*!
    Выводит в поток ошибок сообщение если действительное число является inf или nan
    \param[in] a - действительное число
    \return 
*/
bool assertInfNaN(double a);

/*
    Выводит в поток ошибок сообщение если комплексное число является inf или nan
    Аргументы:
        _Complex double a - комплексное число
    Возвращаемое значение:
        bool
*/
bool assertInfNaNComplex(_Complex double c);

#endif