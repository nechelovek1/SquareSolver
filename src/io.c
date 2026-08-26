#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>
#include <assert.h>

#include "io.h"
#include "solvers.h"
#include "errors.h"

int fClearInputBuffer(FILE* fp)
{
    if (fp == NULL) {
        return -1;
    }

    int ch = fgetc(fp);

    while (ch != '\n' && ch != EOF)
    {
        ch = fgetc(fp);
        continue;
    }

    return 0;
}

int fGetString(FILE* fp, char* str, unsigned int cnt)
{
    if (fp == NULL || str == NULL) {
        return -1;
    }

    if (fgets(str, (int) cnt, fp) == NULL) {
        return -1;
    }
    
    size_t len = strlen(str);

    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }else {
        fClearInputBuffer(fp);
    }

    return 0;
}

int fPrintRoots(FILE* fp, RootsCnt rootsCnt, double x1, double x2)
{
    if (fp == NULL) {
        return -1;
    }

    switch(rootsCnt)
    {
        case ZERO_ROOTS:
            fprintf(fp, "Действительных корней нет\n\n");
            break;
        case ONE_ROOTS:
            fprintf(fp, "x=%.3lg\n\n", x1);
            break;
        case TWO_ROOTS:
            fprintf(fp, "x1=%.3lg x2=%.3lg\n\n", x1, x2);
            break;
        case INF_ROOTS:
            fprintf(fp, "Корнем явялется любое число\n\n");
            break;
        case ERR_ROOTS:
            fprintf(fp, "Решение квадратного уравнения завершилось с ошибкой\n\n");
            break;
        default:
            fprintf(fp, "Неожиданное значение\n\n");
    }

    return 0;
}

int fPrintRootsComplex(FILE* fp, RootsCnt rootsCnt, _Complex double x1, _Complex double x2)
{
    if (fp == NULL) {
        return -1;
    }

    switch(rootsCnt)
    {
        case ZERO_ROOTS:
            fprintf(fp, "Корней нет\n\n");
            break;
        case ONE_ROOTS:
            fprintf(fp, "x1=");
            fPrintComplex(fp, x1);
            fprintf(fp, "\n\n");
            break;
        case TWO_ROOTS:
            fprintf(fp, "x1=");
            fPrintComplex(fp, x1);
            fprintf(fp, " x2=");
            fPrintComplex(fp, x2);
            fprintf(fp, "\n\n");
            break;
        case INF_ROOTS:
            fprintf(fp, "Корнем явялется любое число\n\n");
            break;
        case ERR_ROOTS:
            fprintf(fp, "Решение квадратного уравнения завершилось с ошибкой\n\n");
            break;
        default:
            fprintf(fp, "Неожиданное значение\n\n");
    }

    return -1;
}

int fPrintComplex(FILE* fp, _Complex double c)
{
    if (fp == NULL) {
        return -1;
    }

    if (isequal(cimag(c), 0, EPS)) {
        fprintf(fp, "%lg", creal(c));
    } else if (isequal(creal(c), 0, EPS)) {
        fprintf(fp, "%lgi", cimag(c));
    }else {
        fprintf(fp, "%lg%+lgi", creal(c), cimag(c));
    }

    return 0;
}

//TODO cделать функцию чтения комплексного числ
/*
int fGetComplex(FILE* fp, _Complex double* c)
{
    assert(0);

    return 0;
}
*/

FILE* fOpenDefault(const char* filename, const char* mode, FILE* def)
{
    FILE* fp = NULL;

    if (filename == NULL || mode == NULL) {
        return NULL;
    }

    if (filename[0] == '\0') {
        fp = def;
    } else if ((fp = fopen(filename, mode)) == NULL){
        fprintf(stderr, "Не удалось открыть файл %s\n", filename);
    }

    return fp;
}

int fPrintEquation(FILE* fp, double a, double b, double c)
{
    if (fp == NULL) {
        return -1;
    }
    
    fprintf(fp, "%lgx^2%+lgx%+lg=0\n", a, b, c);

    return 0;
}