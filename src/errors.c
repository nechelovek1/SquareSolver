#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>

#include "errors.h"

bool assertMessage(bool n, const char s[])
{
    if (!n) {
        fprintf(stderr, "%s\n", s);
        return true;
    } else {
        return false;
    }
}

bool assertInfNaN(double a)
{
    if (assertMessage(!isnan(a), "Argument is NaN")) {
        return true;
    }

    if (assertMessage(!isinf(a), "Argument is inf")) {
        return true;
    }

    return false;
}

bool assertInfNaNComplex(_Complex double c) 
{
    if (assertInfNaN(creal(c))) {
        return true;
    }

    if (assertInfNaN(cimag(c))) {
        return true;
    }

    return false;
}
