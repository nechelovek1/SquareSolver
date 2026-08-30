#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "menu.h"
#include "io.h"
#include "loop.h"

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

