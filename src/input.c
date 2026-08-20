#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

int isDouble(const char s[], int n)
{
    int findE = 0, findC = 0;

    if (n == 0) {
        return 0;
    }

    if (s[0] != '-' && s[0] != '+' && !isdigit(s[0])) {
        return 0;
    }

    for (int i = 1; i < n; i ++) {
        if (tolower(s[i]) == 'e') {
            if (!findE) {
                findE = 1;
                if (i == n - 1){
                    return 1;
                } else {
                    return isInt (&s[i + 1], n - i - 1);
                }
            }else{
                return 0;
            }
        } else if (s[i] == '.') {
            if (!findC) {
                findC = 1;
            } else {
                return 0;
            }
        } else if (!isdigit(s[i])) {
            return 0;
        }
    }

    return 1;
}

int isInt(const char s[], int n)
{
    if (n == 0) {
        return 0;
    }

    if (s[0] != '-' && s[0] != '+' && !isdigit(s[0])) {
        return 0;
    }

    for (int i = 1; i < n; i ++) {
        if (!isdigit(s[i])) {
            return 0;
        }
    }

    return 1;
}

int getDouble(double * pd)
{
    char s[100];
    int i = 0;

    char ch;
    ch =  fgetc(stdin);
    while (ch != EOF && ch != ' ' && ch != '\t' && ch != '\n') {
        s[i] = ch;
        i ++;
        ch =  fgetc(stdin);
    }

    if (isDouble(s, strlen(s)) || strcmp(s, "NaN") || strcmp(s, "inf")) {
        *pd = strtod(s, NULL);
        return 1;
    } else {
        return 0;
    }
}

char getFirstChar()
{
    char ch = fgetc(stdin);
    while (fgetc(stdin) != '\n') {
        continue;
    }
    return ch;
}

void clearInputBuffer()
{
    while (getchar() != '\n') {
        continue;
    }
}