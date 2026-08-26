#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

const int MAX_STR_LEN = 100;

typedef struct {
    char inputFilename[MAX_STR_LEN];
    char outputFilename[MAX_STR_LEN];
    bool showComplexRoots;
    bool useComplexEnter;
    bool showHelp;
    bool useParseEquation;
} ProgramOptions;

typedef struct {
    char menuCode;
    const char* menuString;
} MenuPoint;

typedef enum {
    PARSE_OK,
    PARSE_MISSING_ARG,
    PARSE_UNKNOWN_OPT,
    PARSE_OPTIONS_NULL,
} ParseError;

int showSettingsValues(const ProgramOptions* options);
int setDefaultSettings(ProgramOptions* options);
int setUserSettings(ProgramOptions* options);
void showSettingsMenu();
void showMenu();
void printHelpConsole();

/* 
    Парсит опции командной строки
    Принимает на вход
        int argc                - колличество аргументов командной строки (аргумент main)
        char** argv             - аргументы командной строки (аргумент main)
        ProgramOptions* options - указатель на структуру для хранения опций, полученных в результате парсинга
    Возвращает
        PARSE_OK          - парсинг завершился нормально
        PARSE_MISSING_ARG - пропущен обязательный для опции аргумент
        PARSE_UNKNOWN_OPT - неизвестная опция
*/
ParseError parseArgs(int argc, char* argv[], ProgramOptions* options);

#endif