/*!
    \file
    \brief Библиотека для парсинга многочленов и уравнений
*/
#ifndef PARSER_H
#define PARSER_H

/*!
    \brief колличество коэффициентов для парсинга (максимальная степень уравнения + 1)
*/
const int MAX_COEFS = 20; 

/*!
    Преобразует строку-уравнение в массив коэфициентов.
    \param[in] s строка для парсинга
    \param[in] len длина строки (без нулевого символа)
    \param[out] coefs массив для сохранения коэффициентов
    \param[in] coefsCnt длина массива коэффициентов. Длинна массива должна быть равна степени уравнения + 1
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функии возникла ошибка
*/
int parsePolynom(const char s[], unsigned int len, double coefs[], unsigned int coefsCnt);

/*!
    Преобразует строку-многочлен в массив коэфициентов.
    \param[in] s строка для парсинга
    \param[in] len длина строки (без нулевого символа)
    \param[out] coefs массив для сохранения коэффициентов
    \param[in] coefsCnt длина массива коэффициентов. Длинна массива должна быть равна степени многочлена + 1
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функии возникла ошибка
*/
int parseEqation(const char str[], unsigned int len, double coefs[], unsigned int coefsCnt);

int removeSpaces(char* str);

int parseCoef(const char* cptr, double* coef, int* coefLen, int* coefLenWithX);

#endif