#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>

#include "errors.h"

bool assertMessage(bool expressionResult, const char message[])
{
    if (!expressionResult) {
        fprintf(stderr, "%s\n", message);
        return true;
    } else {
        return false;
    }
}

bool assertInfNaN(double d)
{
    if (assertMessage(!isnan(d), "Argument is NaN")) {
        return true;
    }

    if (assertMessage(!isinf(d), "Argument is inf")) {
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
