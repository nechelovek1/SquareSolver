#ifndef TEST_H
#define TEST_H

#include <stdbool.h>

#include "solvers.h"
#include "parser.h"

typedef struct {
    double a, b, c;
    RootsCnt rootsCntRef;
    double x1Ref, x2Ref;
} TestSquare;

typedef struct {
    const char* parseString;
    unsigned int coefsCnt;
    int returnVal;
    double coefs[MAX_COEFS];
} TestParser;

double randomInRange(double mn, double mx);
int runTestSquare(TestSquare testData);
int runTestsSquare(int testsCnt);
void printFailTestMessage(TestSquare testData, RootsCnt rootsCnt, double x1, double x2);
bool compareRootsRefs(double x1, double x2, double x1Ref, double x2Ref);
TestSquare generateTestSquare(RootsCnt rootsCnt);
int runTestParser(TestParser test);
void runTestsParser();



#endif