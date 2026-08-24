#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#include "menu.h"
#include "io.h"

extern char* optarg;

int showSettingsValues(const ProgramOptions* options)
{
    if (options == NULL) {
        return -1;
    }

    printf("| %20s | %20s | %12s | %12s | %10s |\n", "INPUT", "OUTPUT", "COMPL_ROOTS", "COMPL_ENTER", "PARSER");
    
    if (options->inputFilename[0] == '\0') {
        printf("| %20s ", "stdin");
    } else {
        printf("| %20s ", options->inputFilename);
    }

    if (options->outputFilename[0] == '\0') {
        printf("| %20s ", "stdout");
    } else {
        printf("| %20s ", options->outputFilename);
    }
    
    printf("| %12d | %12d ", options->showComplexRoots, options->useComplexEnter);
    printf("| %10d |\n", options->useParseEquation);

    return 0;
}

void showSettingsMenu()
{
    MenuPoint menu[] = {
        {.menuCode = 'i', .menuString = "change input file"},
        {.menuCode = 'o', .menuString = "change output file"},
        {.menuCode = 'r', .menuString = "change option (print complex roots)"},
        {.menuCode = 'c', .menuString = "change option (use complex enter)"},
        {.menuCode = 'p', .menuString = "change option (use parser)"},
        {.menuCode = 'e', .menuString = "exit"}
    };

    int menuLen = sizeof(menu) / sizeof(menu[0]);

    for (int i = 0; i < menuLen; i++) 
    {
        printf("%c) %s\n", menu[i].menuCode, menu[i].menuString);
    }
}

int setDefaultSettings(ProgramOptions* options)
{
    if (options == NULL) {
        return -1;
    }

    options->inputFilename[0] = '\0';
    options->outputFilename[0] = '\0'; 
    options->showComplexRoots = false;
    options->useComplexEnter = false;
    options->useParseEquation = false;

    return 0;
}

int setUserSettings(ProgramOptions* options)
{
    if (options == NULL) {
        return -1;
    }

    int choice = '\0';

    while (choice != 'e' && choice != EOF) {
        showSettingsValues(options);
        showSettingsMenu();
        
        choice = getchar();
        fClearInputBuffer(stdin);

        switch(tolower(choice))
        {
            case 'i':
                printf("Enter input filename (Press Enter for stdin): ");
                fGetString(stdin, options->inputFilename, MAX_STR_LEN);
                break;
            case 'o':
                printf("Enter output filename (Enter for stdout): ");
                fGetString(stdin, options->outputFilename, MAX_STR_LEN);
                break;
            case 'r':
                options->showComplexRoots = !options->showComplexRoots;
                break;
            case 'c':
                options->useComplexEnter = !options->useComplexEnter;
                break;
            case 'p':
                options->useParseEquation = !options->useParseEquation;
                break;     
            case 'e':
                printf("Exit\n");
                break;
            default:
                printf("Unknown\n");
        }
        
    } 

    return 0;
}

void showMenu()
{
    MenuPoint menu[] = {
        {.menuCode = 's', .menuString = "open settings"},
        {.menuCode = 'd', .menuString = "set default settings"},
        {.menuCode = 'r', .menuString = "run solver"},
        {.menuCode = 'e', .menuString = "exit"}
    };
    
    int menuLen = sizeof(menu) / sizeof(MenuPoint);

    for (int i = 0; i < menuLen; i++) 
    {
        printf("%c) %s\n", menu[i].menuCode, menu[i].menuString);
    }
}

void printHelpConsole()
{
    printf(
        "This is a program for solving square equasion.\n"
        "\n"
        "-h show help\n"
        "-i -I <filename> name of input file. If omited, use standart input (console)\n"
        "-o -O <filename> name of output file. If omited, use standart output (console)\n"
        "-c               use complex input\n"
        "-p               use parser for equasions\n"
        "-r               show complex roots\n"
    );
}

ParseError parseArgs(int argc, char* argv[], ProgramOptions* options)
{
    if (options == NULL) {
        return PARSE_OPTIONS_NULL;
    }

    int opt = 0;

    while ((opt = getopt(argc, argv, ":I:i:O:o:hcrp")) != -1) {
        switch(opt)
        {
            case 'I':
            case 'i':
                if (optarg == NULL) {
                    printf("Missing argument after -i\n");
                    return PARSE_MISSING_ARG;
                }
                strncpy(options->inputFilename, optarg, MAX_STR_LEN);
                break;
            case 'O':
            case 'o':
                if (optarg == NULL) {
                    printf("Missing argument after -o\n");
                    return PARSE_MISSING_ARG;
                }
                strncpy(options->outputFilename, optarg, MAX_STR_LEN);
                break;
            case 'h':
                options->showHelp = true;
                break;
            case 'c':
                options->useComplexEnter = true;
                break;
            case 'r':
                options->showComplexRoots = true;
                break;
            case 'p':
                options->useParseEquation = true;
                break;
            default:
                printf("Unknown option: %c\n", opt);
                return PARSE_UNKNOWN_OPT;
        }
    }
    
    return PARSE_OK;
}