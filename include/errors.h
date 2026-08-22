#ifndef ERRORS_H
#define ERRORS_H

#include <stdbool.h>
#include <complex.h>

bool assertMessage(bool, const char[]);
bool assertInfNaN(double a);
bool assertInfNaNComplex(_Complex double c);


#endif