#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "solvers.h"

//int getDouble(double *);


int main()
{
    double a = 0, b = 0, c = 0;
    printf("Введите коэффициенты a, b, c уравнения ax^2+bx+c=0\n");
    if (scanf("%lg %lg %lg", &a, &b, &c) != 3) {
        printf("Ошибка ввода\n");
        return -1;
    }

    double x1 = 0, x2 = 0;
    RootsCnt rootsCnt = squareSolver(a, b, c, &x1, &x2);
    
    switch(rootsCnt) {
        case ZERO_ROOTS:
            printf("Действительных корней нет\n");
            break;
        case ONE_ROOTS:
            printf("%.3lg\n", x1);
            break;
        case TWO_ROOTS:
            printf("%.3lg %.3lg\n", x1, x2);
            break;
        case INF_ROOTS:
            printf("Любое число\n");
            break;
        case ERR_ROOTS:
            printf("Решение квадратного уравнения завершилось с ошибкой\n");
            break;
        default:
            printf("Неожиданное значение\n");
    }

    return 0;
}
