#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"

int parsePolynom(const char s[], unsigned int len, double coefs[], unsigned int coefsCnt)
{
    if (s == NULL || coefs == NULL) {
        return -1;
    }

    double coef = 0;
    unsigned int power = 0;
    int coefLen = 0, coefLenWithX = 0, powerLen = 0;

    const char* cptr = s;

    if (sscanf(cptr, "x%n", &coefLenWithX) != EOF && coefLenWithX == 1) {
        coefLen = 0;
        coef = 1;
        power = 1;
    } else if (parseCoef(cptr, &coef, &coefLen, &coefLenWithX) == -1) {
        return -1;
    }

    cptr += coefLenWithX;

    if (coefLen == coefLenWithX || coefLenWithX == 0) {
        power = 0;
    } else if (cptr - s < len) {
        sscanf(cptr, "^%u%n", &power, &powerLen);
        cptr += powerLen;
        if (powerLen == 0) {
            power = 1;
        } else if (powerLen == 1) {
            return -1;
        } 
    }

    if (power < coefsCnt){
        coefs[coefsCnt - 1 - power] += coef;
        //printf("%u %lg\n", power, coef);
    } else {
        return -1;
    }

    while (cptr - s < len)
    {
        coef = 0;
        power = 0;
        coefLen = 0, coefLenWithX = 0, powerLen = 0;

        if (*cptr != '+' && *cptr != '-') {
            return -1;
        }
        
        if (parseCoef(cptr, &coef, &coefLen, &coefLenWithX) == -1) {
            return -1;
        }

        if (coefLenWithX != 0) {
            cptr += coefLenWithX;
        } else {
            cptr += coefLen;
        }
        //Этот кусок тоже можно заменить функцией
        if (coefLen == coefLenWithX || coefLenWithX == 0) {
            power = 0;
        } else if (cptr - s < len) {
            sscanf(cptr, "^%u%n", &power, &powerLen);
            cptr += powerLen;
            if (powerLen == 0) {
                power = 1;
            } else if (powerLen == 1) {
                return -1;
            } 
        }

        if (power < coefsCnt){
            //printf("%u %lg\n", power, coef);
            coefs[coefsCnt - 1 - power] += coef;
        } else {
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

    double coefsLeft[MAX_COEFS] = {};
    double coefsRight[MAX_COEFS] = {};

    const char *left = s;
    const char *right = strchr(s, '=');

    if (right == NULL) {
        return -1;
    }

    //проверка является ли '=' последним символом строки
    if (right == s + len - 1) {
        return -1;
    }
    //проверка является ли '=' первым символом строки
    if (right == s) {
        return -1;
    }
    
    unsigned int lenLeft = (unsigned int) (right - s);
    //в случае успешной инициализации right укаазывает на '='. Чтобу указатель был на начало правой части, его нужно увеличить на 1
    right++;
    //разница len и lenLeft - длина правой части включая пробельный символ
    unsigned int lenRight = (len - lenLeft - 1);    

    if ((parsePolynom(left, lenLeft, coefsLeft, coefsCnt) == -1) || (parsePolynom(right, lenRight, coefsRight, coefsCnt) == -1)) {
        return -1;
    }

    for (unsigned int i = 0; i < coefsCnt; i++) {
        coefs[i] = coefsLeft[i] - coefsRight[i];
    }

    return 0;
}

int removeSpaces(char* str)
{
    if (str == NULL) {
        return -1;
    }

    unsigned int newIdx = 0;
    size_t len = strlen(str);
    for (unsigned int idx = 0; idx < len; idx++)
    {
        if (!isspace(str[idx])) {
            str[newIdx] = str[idx];
            newIdx++;
        }
    }

    str[newIdx] = '\0';

    return 0;
}

int parseCoef(const char* cptr, double* coef, int* coefLen, int* coefLenWithX)
{
    sscanf(cptr, "%lf%nx%n", coef, coefLen, coefLenWithX);
    
    if (coefLen == 0) {
        if (sscanf(cptr, "-x%n", coefLenWithX) != EOF && *coefLenWithX == 2) {
            *coefLen = 1;
            *coef = -1;
        } else if (sscanf(cptr, "+x%n", coefLenWithX) != EOF && *coefLenWithX == 2) {
            *coefLen = 1;
            *coef = 1;
        } else {
            return -1;
        }
    }

    return 0;
}

/*int parsePower(const char* cptr, unsigned int* power, int* powerLen)
{
    sscanf(cptr, "^%u%n", &power, &powerLen);
    cptr += powerLen;
    if (powerLen == 0) {
        power = 1;
    } else if (powerLen == 1) {
        return -1;
    } 
}*/