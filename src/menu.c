#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "menu.h"

//TODO перенести в другой файл
void fClearInputBuffer(FILE* fp)
{
    int ch = fgetc(fp);

    while (ch != '\n' && ch != EOF)
    {
        ch = fgetc(fp);
        continue;
    }
}
//TODO перенести в другой файл
void fGetString(char * str, int cnt, FILE* fp)
{
    fgets(str, cnt, fp);
    
    size_t len = strlen(str);

    if (str[len - 1] == '\n') {
        str[len - 1]= '\0';
    }else {
        fClearInputBuffer(fp);
    }
}

void showSettingsValues(const ProgramOptions* options)
{
    printf("| %20s | %20s | %12s | %12s | %10s |\n", "INPUT", "OUTPUT", "COMPL_ROOTS", "COMPL_ENTER", "PARSER");
    
    if (strlen(options->inputFilename) == 0) {
        printf("| %20s ", "stdin");
    } else {
        printf("| %20s ", options->inputFilename);
    }

    if (strlen(options->outputFilename) == 0) {
        printf("| %20s ", "stdout");
    } else {
        printf("| %20s ", options->outputFilename);
    }
    
    printf("| %12d | %12d ", options->showComplexRoots, options->useComplexEnter);
    printf("| %10d |\n", options->useParseEquation);
}

void showSettingsMenu()
{
    MenuPoint menu[] = {
        {.menuCode = 'i', .menuString = "change input file"},
        {.menuCode = 'o', .menuString = "change output file"},
        {.menuCode = 'r', .menuString = "change option (print complex roots)"},
        {.menuCode = 'e', .menuString = "change option (use complex enter)"},
        {.menuCode = 'p', .menuString = "change option (use parser)"},
        {.menuCode = 'x', .menuString = "exit"}
    };

    int menuLen = sizeof(menu) / sizeof(MenuPoint);

    for (int i = 0; i < menuLen; i++) 
    {
        printf("%c) %s\n", menu[i].menuCode, menu[i].menuString);
    }
}

void setDefaultSettings(ProgramOptions* options)
{
    options->inputFilename[0] = '\0';
    options->outputFilename[0] = '\0'; 
    options->showComplexRoots = false;
    options->useComplexEnter = false;
    options->useParseEquation = false;
}

void setUserSettings(ProgramOptions* options)
{
    int choice = ' ';

    while (choice != 'x' && choice != EOF) {
        showSettingsValues(options);
        showSettingsMenu();
        
        choice = getchar();
        fClearInputBuffer(stdin);

        switch(tolower(choice))
        {
            case 'i':
                printf("Enter input filename (Press Enter for stdin): ");
                fGetString(options->inputFilename, MAX_STR_LEN, stdin);
                break;
            case 'o':
                printf("Enter output filename (Enter for stdout): ");
                fGetString(options->outputFilename, MAX_STR_LEN, stdin);
                break;
            case 'r':
                options->showComplexRoots = !options->showComplexRoots;
                break;
            case 'e':
                options->useComplexEnter = !options->useComplexEnter;
                break;
            case 'p':
                options->useParseEquation = !options->useParseEquation;
                break;     
            case 'x':
                printf("Exit\n");
                break;
            default:
                printf("Unknown\n");
        }
        
    } 
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