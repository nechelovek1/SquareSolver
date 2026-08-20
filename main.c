#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "solvers.h"
#include "input.h"

void printRoots(RootsCnt, double, double);

int main(int argc, char * argv[])
{
    char ch = ' ';
    printf("Программа для решения квадратных уравнений\n"
            "введите e для выхода или любой символ для продолжения\n");
    ch = getFirstChar();

    while(ch != EOF && tolower(ch) != 'e')
    {
        double a = 0, b = 0, c = 0;
        printf("Введите коэффициенты a, b, c уравнения ax^2+bx+c=0\n");
        if (scanf("%lg %lg %lg", &a, &b, &c) != 3) {
            printf("Ошибка ввода\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        double x1 = 0, x2 = 0;
        RootsCnt rootsCnt = squareSolver(a, b, c, &x1, &x2);
        
        printRoots(rootsCnt, x1, x2);

        printf("Введите e для выхода или любой символ для продолжения\n");
        ch = getFirstChar();
    }

    printf("Завершено\n");

    return 0;
}

void printRoots(RootsCnt rootsCnt, double x1, double x2)
{
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
}

