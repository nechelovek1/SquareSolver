#ifndef PARSER_H
#define PARSER_H

const int MAX_COEFS = 20;

/*
    Преобразует строку-уравнение в массив коэфициентов.
    Аргументы:
        const char s[]        - строка для парсинга
        unsigned int len      - длина строки
        double coefs[]        - массив для сохранения коэффициентов
        undigned int coefsCnt - длина массива коэффициентов. Длинна массива должна быть равна степени уравнения + 1
    Возвращаемое значение:
        0  - функция выполнилась без ошибок
        -1 - в результате выполнения функии возникла ошибка
*/
int parsePolynom(const char s[], unsigned int len, double coefs[], unsigned int coefsCnt);

/*
    Преобразует строку-многочлен в массив коэфициентов.
    Аргументы:
        const char s[]        - строка для парсинга
        unsigned int len      - длина строки
        double coefs[]        - массив для сохранения коэффициентов
        undigned int coefsCnt - длина массива коэффициентов. Длинна массива должна быть равна степени многочлена + 1
    Возвращаемое значение
        0  - функция выполнилась без ошибок
        -1 - в результате выполнения функии возникла ошибка
*/
int parseEqation(const char s[], unsigned int len, double coefs[], unsigned int coefsCnt);

#endif