#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <complex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "solvers.h"
#include "errors.h"

const double EPS = 1e10;

typedef struct {
    double a;
    double b;
    double c;
    RootsCnt rootsCntRef;
    double x1Ref;
    double x2Ref;
} TestSquare;


void plotParabol(double a, double b, double c);
double calcParabol(double a, double b, double c, double x);
bool parseEqasion(char s[], double coefs[]);
double randomInRange(double mn, double mx);


int runTest(TestSquare testData);
int runTests(int testsCnt);
void printFailTestMessage(TestSquare testData, RootsCnt rootsCnt, double x1, double x2);
bool compareRootsRefs(double x1, double x2, double x1Ref, double x2Ref);
TestSquare generateTest();

int main(int argc, const char* argv[])
{
    runTests(100);

    return 0;
}

double calcParabol(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}
void plotParabol(double a, double b, double c)
{   
    int screensize = 40;
    char screen[screensize][screensize];
    for (int i = 0; i < screensize; i++) 
    {
        for (int j = 0; j < screensize; j++) 
        {
            screen[i][j] = ' ';
        }
    }

    for (int i = 0; i < screensize; i++) 
    {
        screen[i][screensize / 2] = '|';
        screen[screensize / 2][i] = '_';
    }

    for (int i = -screensize / 2; i < screensize / 2; i++) 
    {
        double yr = calcParabol(a, b, c, i);
        double yl = calcParabol(a, b, c, i + 1);
        double ym = (yr + yl) / 2;
        int j = (int) ym;
        if (j >= -screensize / 2 && j < screensize / 2) {
            screen[-j + screensize / 2][i + screensize / 2] = '*';
        }
    }

    for (int i = 0; i < screensize; i++) 
    {
        for (int j = 0; j < screensize; j++) 
        {
            putchar(screen[i][j]);
        }
        putchar('\n');
    }
}


bool parseEqation(char s[], double coefs[])
{
    int len = strlen(s);
    bool findSign = false;

    
    double coef = 0.0;
    int power = 0;

    char* endptr = NULL, * startptr = s;

    for (int i = 0; i < len; i++) {
        if (s[i] == '-' || s[i] == '+') {
            if (findSign) {
                return false;
            } else {
                findSign = true;
                startptr = &s[i];
                continue;
            }
        } else if (tolower(s[i]) == 'x') {
            coef = strtod(startptr, &endptr);
            if (endptr != )
        }
    }
}

void printFailTestMessage(TestSquare testData, RootsCnt rootsCnt, double x1, double x2)
{
    printf("Test FAILED: a=%lg, b=%lg, c=%lg\n"
           "Expected %d roots, x1ref=%lg, x2ref=%lg\n"
           "Got:     %d roots, x1=%lg,    x2=%lg\n",
           testData.a, testData.b, testData.c, 
           testData.rootsCntRef, testData.x1Ref, testData.x2Ref,
           rootsCnt, x1, x2 
    );
}

int runTest(TestSquare testData) 
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
    return ((isequal(x1, x1Ref, EPS) && isequal(x2, x2Ref, EPS)) || (isequal(x1, x2Ref, EPS) && isequal(x2, x1Ref, EPS)));
}

double randomInRange(double mn, double mx)
{
    srand(time(NULL));

    double randVal = (double) rand() / RAND_MAX;
    return mn + randVal * (mx - mn);
}

TestSquare generateTest()
{
    double x1 = 0, x2 = 0;
    const int mn = -100, mx = 100;

    TestSquare test;

    test.x1Ref = randomInRange(mn, mx);
    test.x2Ref = randomInRange(mn, mx);

    test.a = randomInRange(mn, mx);
    test.b = -test.a*(test.x1Ref + test.x2Ref);
    test.c = test.a * test.x1Ref * test.x2Ref;

    if (isequal(test.x1Ref, test.x2Ref, EPS)) {
        test.rootsCntRef = ONE_ROOTS;
    } else {
        test.rootsCntRef = TWO_ROOTS;
    }

    return test;
}


int runTests(int testsCnt)
{   
    TestSquare testsSpec[] = {
        {0, 0, 0, INF_ROOTS, NAN, NAN},
        {0, 0, 1, ZERO_ROOTS, NAN, NAN},
        {0, 1, 0, ONE_ROOTS, 0, NAN},
        {0, 1, 2, ONE_ROOTS, -2, NAN},
        {NAN, 0, 0, ERR_ROOTS, NAN, NAN},
        {0, NAN, 0, ERR_ROOTS, NAN, NAN},
        {0, 0, NAN, ERR_ROOTS, NAN, NAN},
        {1.0/0.0, 0, 0, ERR_ROOTS, NAN, NAN},
        {0, 1.0/0.0, 0, ERR_ROOTS, NAN, NAN},
        {0, 0, 1.0/0.0, ERR_ROOTS, NAN, NAN},
    };
    
    size_t testsSpecCnt = sizeof(testsSpec) / sizeof(TestSquare);
    
    for (int i = 0; i < testsSpecCnt; i++) {
        runTest(testsSpec[i]);
    }

    for (int i = 0; i < testsCnt; i++) {
        TestSquare test = generateTest();
        runTest(test);
    }
    return 1;
}