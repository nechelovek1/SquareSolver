#include <stdio.h>
#include "errors.h"

int assertMessage(int n, const char s[])
{
    if (!n) {
        printf("%s\n", s);
        return 1;
    } else {
        return 0;
    }
}