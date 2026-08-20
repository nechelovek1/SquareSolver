#include <stdio.h>
#include <ctype.h>
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
    char ch;
    if(fscanf(stdin, "%lg", pd) == 1){
        ch = fgetc(stdin);
        return 1;
    } else {
        fscanf(stdin, "%s", s);
        return 0;
    }
}

char getChar()
{
    
}