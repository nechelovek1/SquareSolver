#ifndef TEST_H
#define TEST_H

#include <stdbool.h>

#include "solvers.h"

typedef struct {
    double a, b, c;
    RootsCnt rootsCntRef;
    double x1Ref, x2Ref;
} TestSquare;

double randomInRange(double mn, double mx);
int runTest(TestSquare testData);
int runTests(int testsCnt);
void printFailTestMessage(TestSquare testData, RootsCnt rootsCnt, double x1, double x2);
bool compareRootsRefs(double x1, double x2, double x1Ref, double x2Ref);
TestSquare generateTestSquare(RootsCnt rootsCnt);


#endif