#ifndef LOOP_H
#define LOOP_H

#include <stdlib.h>

#include "menu.h"
#include "io.h"
#include "bmp.h"

const int MAX_BMP_FILENAME_LEN = MAX_STR_LEN + 17;

int solveSquareInLoop(const ProgramOptions* options);
int getCoefs(const ProgramOptions* options, FILE* input, double* a, double* b, double* c);
int drawSquareEquation(const char* filename, RootsCnt rootsCnt, double a, double b, double c, double x1, double x2);

#endif