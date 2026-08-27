#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "tests.h"
#include "solvers.h"
#include "parser.h"

#define INF INFINITY

void printFailTestMessage(TestSquare testData, RootsCnt rootsCnt, double x1, double x2)
{
    printf("Test FAILED: a=%.10lf, b=%.10lf, c=%.10lf\n"
           "Expected %d roots, x1ref=%.10lf, x2ref=%.10lf\n"
           "Got:     %d roots, x1=%.10lf,    x2=%.10lf\n",
           testData.a, testData.b, testData.c, 
           testData.rootsCntRef, testData.x1Ref, testData.x2Ref,
           rootsCnt, x1, x2 
    );
}

int runTestSquare(TestSquare testData) 
{
    double x1 = NAN, x2 = NAN;
    RootsCnt rootsCnt = solveSquare(testData.a, testData.b, testData.c, &x1, &x2);
    if (rootsCnt != testData.rootsCntRef) {
        printFailTestMessage(testData, rootsCnt, x1, x2);
        return 0;
    } else if (rootsCnt == ERR_ROOTS || rootsCnt == ZERO_ROOTS) {
        return 1;      
    } else if ((rootsCnt == ONE_ROOTS) && !(isequal(x1, testData.x1Ref, EPS) || isequal(x2, testData.x1Ref, EPS))) {
        printFailTestMessage(testData, rootsCnt, x1, x2);
        return 0;
    } else if ((rootsCnt == TWO_ROOTS) && !compareRootsRefs(x1, x2, testData.x1Ref, testData.x2Ref)){
        printFailTestMessage(testData, rootsCnt, x1, x2);
        return 0;
    } else {
        return 1;
    }
}

bool compareRootsRefs(double x1, double x2, double x1Ref, double x2Ref) 
{
    return ((isequal(x1, x1Ref, EPS) && isequal(x2, x2Ref, EPS)) || 
            (isequal(x1, x2Ref, EPS) && isequal(x2, x1Ref, EPS)));
}

double randomInRange(double mn, double mx)
{
    double randVal = (double) rand() / RAND_MAX;
    return mn + randVal * (mx - mn);
}

TestSquare generateTestSquare(RootsCnt rootsCnt)
{
    const int mn = -100, mx = 100;

    TestSquare test;

    test.x1Ref = randomInRange(mn, mx);

    switch(rootsCnt)
    {
        case ONE_ROOTS:
            test.rootsCntRef = ONE_ROOTS;
            test.x2Ref = test.x1Ref;
            break;
        case TWO_ROOTS:
            test.rootsCntRef = TWO_ROOTS;
            test.x2Ref = randomInRange(mn, mx);
            break;           
        default:
            test.rootsCntRef = TWO_ROOTS;
            test.x2Ref = randomInRange(mn, mx);
            break;                
    }

    test.a = randomInRange(mn, mx);
    test.b = -test.a * (test.x1Ref + test.x2Ref);
    test.c = test.a * test.x1Ref * test.x2Ref;

    return test;
}

int runTestsSquare(int testsCnt)
{   
    int successCnt = 0;

    TestSquare testsSpec[] = {
        {.a = 0,   .b = 0,   .c = 0,   .rootsCntRef = INF_ROOTS,  .x1Ref = NAN, .x2Ref = NAN},
        {.a = 0,   .b = 0,   .c = 1,   .rootsCntRef = ZERO_ROOTS, .x1Ref = NAN, .x2Ref = NAN},
        {.a = 0,   .b = 1,   .c = 0,   .rootsCntRef = ONE_ROOTS,  .x1Ref = 0,   .x2Ref = NAN},
        {.a = 0,   .b = 1,   .c = 2,   .rootsCntRef = ONE_ROOTS,  .x1Ref = -2,  .x2Ref = NAN},
        {.a = NAN, .b = 0,   .c = 0,   .rootsCntRef = ERR_ROOTS,  .x1Ref = NAN, .x2Ref = NAN},
        {.a = 0,   .b = NAN, .c = 0,   .rootsCntRef = ERR_ROOTS,  .x1Ref = NAN, .x2Ref = NAN},
        {.a = 0,   .b = 0,   .c = NAN, .rootsCntRef = ERR_ROOTS,  .x1Ref = NAN, .x2Ref = NAN},
        {.a = INF, .b = 0,   .c = 0,   .rootsCntRef = ERR_ROOTS,  .x1Ref = NAN, .x2Ref = NAN},
        {.a = 0,   .b = INF, .c = 0,   .rootsCntRef = ERR_ROOTS,  .x1Ref = NAN, .x2Ref = NAN},
        {.a = 0,   .b = 0,   .c = INF, .rootsCntRef = ERR_ROOTS,  .x1Ref = NAN, .x2Ref = NAN},
    };

    srand(time(NULL));

    size_t testsSpecCnt = sizeof(testsSpec) / sizeof(*testsSpec);
    
    for (int i = 0; i < testsSpecCnt; i++) {
        successCnt += runTestSquare(testsSpec[i]);
    }

    for (int i = 0; i < testsCnt; i++) {
        TestSquare test2 = generateTestSquare(TWO_ROOTS);
        successCnt +=  runTestSquare(test2);
        TestSquare test1 = generateTestSquare(ONE_ROOTS);
        successCnt +=  runTestSquare(test1);
    }
    return successCnt;
}

int runTestParser(TestParser test)
{
    const unsigned int coefsCnt = 3;
    double coefs[coefsCnt] = {};
    
    int returnVal = parseEqation(test.parseString, strlen(test.parseString), coefs, coefsCnt);
    
    if (returnVal != test.returnVal) {
        printf("Test FAILED\n");
    } else if (returnVal == -1) {
        return 1;
    }

    for (unsigned int i = 0; i < test.coefsCnt; i++)
    {
        if (!isequal(coefs[i], test.coefs[i], EPS)) {
            printf("Test FAILED\n");
            return 0;
        }
    }

    return 1;
    
}

void runTestsParser()
{
    TestParser tests[] = {
        {"x^2+x+3+4x+5=0",              3, 0,  {1,    5,    8}},
        {"2.3x-3+4x^2=x-x+6",           3, 0,  {4,    2.3,  9}},
        {"0=0",                         3, 0,  {0,    0,    0}},
        {"x=x",                         3, 0,  {0,    0,    0}},
        {"lksdhlksdahflsa",             3, -1},
        {"+xxxx=-xxxxx",                3, -1},
        {"2.3x-3+4x^2.1=x-x+6",         3, -1},
    };

    unsigned int testsCnt = sizeof(tests) / sizeof(tests[0]);
    unsigned int correct = 0;

    for (unsigned int i = 0; i < testsCnt; i++)
    {
        if(runTestParser(tests[i])) {
            printf("Test %u done", i);
            correct++;
        }
    }
    printf("%lg\n", (double) correct / testsCnt);

}