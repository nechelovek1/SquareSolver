#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "solvers.h"
#include "menu.h"
#include "io.h"
#include "parser.h"
#include "bmp.h"

int solveSquareInLoop(const ProgramOptions* options);
int getCoefs(const ProgramOptions* options, FILE* input, double* a, double* b, double* c);
int drawSquareEquation(const char* filename, RootsCnt rootsCnt, double a, double b, double c, double x1, double x2);

const int MAX_BMP_FILENAME_LEN = MAX_STR_LEN + 17;

int main(int argc, char* argv[])
{
    ProgramOptions options = {.inputFilename = "", .outputFilename = ""};

    ParseError parseRes = parseArgs(argc, argv, &options);
    if (parseRes) {
        return -1;
    }

    if (options.showHelp) {
        printHelpConsole();
        return 0;
    }

    printf("Program for solving quadratic equations\n");
    
    showSettingsValues(&options);
    solveSquareInLoop(&options);
    printf("Solve loop done\n");

    int choice = '\0';

    while (choice != EOF && choice != 'e') 
    {
        showMenu();

        choice = getchar();
        fClearInputBuffer(stdin);

        switch(tolower(choice)) 
        {
            case 'd':
                setDefaultSettings(&options);
                break;
            case 's':
                setUserSettings(&options);
                break;
            case 'e':
                break;
            case 'r':
                showSettingsValues(&options);
                solveSquareInLoop(&options);
                printf("Solve loop done\n");
                break;
            default:
                printf("Unknown\n");
        }
        
    }

    printf("Done\n");

    return 0;
}

int solveSquareInLoop(const ProgramOptions* options)
{
    int equationsCnt = 0;

    if (options == NULL) {
        return -1;
    }

    FILE* input = NULL;
    FILE* output = NULL;

    input = fOpenDefault(options->inputFilename, "r", stdin);
    if (input == NULL) {
        return -1;
    }
    output = fOpenDefault(options->outputFilename, "a", stdout);
        if (output == NULL) {
        return -1;
    }

    while(true)
    {
        if (input == stdin) {
            printf("Enter e for exit and any char for continue: ");

            int choice = getchar();
            fClearInputBuffer(input);

            if (tolower(choice) == 'e' || choice == EOF) {
                break;
            }

            if (options->useParseEquation)
            {
                printf("Enter equation ax^2+bx+c+...=dx^2+ex+f+...(without spaces)\n");
            } else {
                printf("Enter coefs a, b, c of equation ax^2+bx+c=0\n");
            }
        }

        double a = 0, b = 0, c = 0;
        double x1 = 0, x2 = 0;
        _Complex double cx1 = 0, cx2 = 0;
        RootsCnt rootsCnt = ZERO_ROOTS;

        int getCoefsRes = getCoefs(options, input, &a, &b, &c);
        if (getCoefsRes == -1) {
            continue;
        }

        if (options->showComplexRoots) {
            rootsCnt = solveSquareComplex(a, b, c, &cx1, &cx2);
            fPrintEquation(output, a, b, c);
            fPrintRootsComplex(output, rootsCnt, cx1, cx2);

            if (isequal(cimag(cx1), 0, EPS) && isequal(cimag(cx2), 0, EPS)) {
                x1 = creal(cx1);
                x2 = creal(cx2);
            } else {
                rootsCnt = ZERO_ROOTS;
            }
        } else {
            rootsCnt = solveSquare(a, b, c, &x1, &x2);
            fPrintEquation(output, a, b, c);
            fPrintRoots(output, rootsCnt, x1, x2);
        }

        if (options->drawGraph) {
            char bmpFilename[MAX_BMP_FILENAME_LEN];
            snprintf(bmpFilename, MAX_BMP_FILENAME_LEN, "%s_%d.bmp", options->bmpName, equationsCnt);
            drawSquareEquation(bmpFilename, rootsCnt, a, b, c, x1, x2);
            equationsCnt++;
        }
    }

    if (output != stdout) {
        fclose(output);
    }
    if (input != stdin) {
        fclose(input);
    }

    return 0;
}

int getCoefs(const ProgramOptions* options, FILE* input, double* a, double* b, double* c)
{
    if (options == NULL || input == NULL) {
        return -1;
    }

    if (options->useParseEquation) {
        const unsigned int coefsCnt = 3;

        double coefs[coefsCnt] = {};
        char equation[MAX_STR_LEN] = {};

        if (fGetString(input, equation, MAX_STR_LEN) == -1) {
            //break;
            return -1;
        }

        removeSpaces(equation);

        if (parseEqation(equation, (unsigned int) strlen(equation), coefs, coefsCnt) == -1) {
            printf("Parser error\n");
            //continue;
            return -1;
        } else {
            *a = coefs[2];
            *b = coefs[1];
            *c = coefs[0];
        }

    } else {
        int scanfRes = fscanf(input, "%lg %lg %lg", a, b, c);
        if (scanfRes == EOF) {
            return -1;
            //break;
        } else if (scanfRes != 3) {
            printf("Enter error\n");
            fClearInputBuffer(input);
            //continue;
            return -1;
        }
        fClearInputBuffer(input);
    }

    return 0;
}

int drawSquareEquation(const char* filename, RootsCnt rootsCnt, double a, double b, double c, double x1, double x2)
{
    if (filename == NULL)
    {
        return -1;
    }

    if (rootsCnt == ERR_ROOTS) {
        return -1;
    }

    BmpOptions fileOptions = {};

    unsigned int height = 1920;
    unsigned int width = 1080;

    openBmp(filename, &fileOptions, height, width);

    GraphOptions graphOptions = {.centerX = 1000, .centerY = 500, .pixelsPerUnit = 25, .samplesPerPixel = 100};

    setColorBmp(&fileOptions, BMP_GREY);    
    drawGrid(&fileOptions, &graphOptions);

    setColorBmp(&fileOptions, BMP_WHITE);    
    drawAxes(&fileOptions, &graphOptions);

    const int coefsCnt = 3;
    double coefs[coefsCnt] = {c, b, a};

    setColorBmp(&fileOptions, BMP_YELLOW);
    drawPolynom(&fileOptions, &graphOptions, coefs, coefsCnt);

    setColorBmp(&fileOptions, BMP_BLUE);

    if (rootsCnt == ONE_ROOTS) {
        drawGraphPoint(&fileOptions, &graphOptions, x1, 0);
    } else if (rootsCnt == TWO_ROOTS) {
        drawGraphPoint(&fileOptions, &graphOptions, x1, 0);
        drawGraphPoint(&fileOptions, &graphOptions, x2, 0);
    }

    writeBitmapBmp(&fileOptions);
    closeBmp(&fileOptions);

    return 0;
}