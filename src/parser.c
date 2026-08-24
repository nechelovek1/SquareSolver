#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int parsePolynom(const char s[], unsigned int len, double coefs[], unsigned int coefsCnt)
{
    if (s == NULL || coefs == NULL) {
        return -1;
    }

    const char* cptr = s;

    while (cptr - s < len)
    {
        double coef = 0;
        unsigned int power = 0;
        int coefLen = 0, coefLenWithX = 0, powerLen = 0;

        sscanf(cptr, "%lf%nx%n", &coef, &coefLen, &coefLenWithX);
        
        if (coefLen == 0) {
            if (sscanf(cptr, "-x%n", &coefLenWithX) != EOF && coefLenWithX == 2) {
                coefLen = 1;
                coef = -1;
            } else if (sscanf(cptr, "+x%n", &coefLenWithX) != EOF && coefLenWithX == 2) {
                coefLen = 1;
                coef = 1;
            } else if (sscanf(cptr, "x%n", &coefLenWithX) != EOF && coefLenWithX == 1) {
                coefLen = 0;
                coef = 1;
            } else {
                return -1;
            }
        }

        if (coefLenWithX != 0) {
            cptr += coefLenWithX;
        } else {
            cptr += coefLen;
        }

        if (coefLen == coefLenWithX || coefLenWithX == 0) {
            power = 0;
        } else if (cptr - s < len) {
            sscanf(cptr, "^%u%n", &power, &powerLen);
            cptr += powerLen;
            if (powerLen == 0) {
                power = 1;
            } else if (powerLen == 1) {
                printf("2down");
                return -1;
            } 
        }

        if (power < coefsCnt){
            coefs[coefsCnt - 1 - power] += coef;
        } else {
            printf("1down");
            return -1;
        }
    }

    return 0;
}

int parseEqation(const char s[], unsigned int len, double coefs[], unsigned int coefsCnt)
{
    if (s == NULL || coefs == NULL) {
        return -1;
    }

    double coefsLeft[MAX_COEFS];
    double coefsRight[MAX_COEFS];

    const char *left = s;
    const char *right = strchr(s, '=');

    if (right == NULL) {
        return -1;
    }

    //проверка является ли '=' последним символом строки
    if (right == s + len - 1) {
        return -1;
    }
    
    unsigned int lenLeft = (unsigned int) (right - s);
    //в случае успешной инициализации right укаазывает на '='. Чтобу указатель был на начало правой части, его нужно увеличить на 1
    right++;
    //разница len и lenLeft - длина правой части включая пробельный символ
    unsigned int lenRight = (len - lenLeft - 1);    

    for (unsigned int i = 0; i < coefsCnt; i++) 
    {
        coefsLeft[i] = 0;
        coefsRight[i] = 0;
    }

    if ((parsePolynom(left, lenLeft, coefsLeft, coefsCnt) == -1) || (parsePolynom(right, lenRight, coefsRight, coefsCnt) == -1)) {
        return -1;
    }

    for (unsigned int i = 0; i < coefsCnt; i++) {
        coefs[i] = coefsLeft[i] - coefsRight[i];
    }

    return 0;
}