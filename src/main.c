#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#include "solvers.h"
#include "menu.h"
#include "io.h"
#include "parser.h"

int solveSquareInLoop(const ProgramOptions* options);

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

    int choice = ' ';

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

            if (tolower(choice) == 'e') {
                break;
            }

            if (options->useParseEquation)
            {
                printf("Enter equation ax^2+bx+c+...=dx^2+ex+f+...\n");
            } else {
                printf("Enter coefs a, b, c of equation ax^2+bx+c=0\n");
            }
        }

        double a = 0, b = 0, c = 0;

        if (options->useParseEquation) {
            const unsigned int coefsCnt = 3;

            double coefs[coefsCnt] = {};
            char equation[MAX_STR_LEN] = {};

            if (fGetString(input, equation, MAX_STR_LEN) == -1) {
                break;
            }

            if (parseEqation(equation, strlen(equation), coefs, coefsCnt) == -1) {
                printf("Parser error\n");
                continue;
            } else {
                a = coefs[0];
                b = coefs[1];
                c = coefs[2];
            }

        } else {
            int scanfRes = fscanf(input, "%lg %lg %lg", &a, &b, &c);
            if (scanfRes == EOF) {
                break;
            } else if (scanfRes != 3) {
                fprintf(output, "Enter error\n");
                fClearInputBuffer(input);
                continue;
            }
            fClearInputBuffer(input);
        }

        if (options->useComplexEnter || options->showComplexRoots) {
            _Complex double x1 = 0, x2 = 0;
            RootsCnt rootsCnt = solveSquareComplex(a, b, c, &x1, &x2);
            fPrintEquation(output, a, b, c);
            fPrintRootsComplex(output, rootsCnt, x1, x2);
        } else {
            double x1 = 0, x2 = 0;
            RootsCnt rootsCnt = solveSquare(a, b, c, &x1, &x2);
            fPrintEquation(output, a, b, c);
            fPrintRoots(output, rootsCnt, x1, x2);
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
