#ifndef MENU_H
#define MENU_H

const int MAX_STR_LEN = 100;

typedef struct {
    char inputFilename[MAX_STR_LEN];
    char outputFilename[MAX_STR_LEN];
    bool showComplexRoots;
    bool useComplexEnter;
    bool showHelp;
    bool useParseEquation;
} ProgramOptions;

void showSettingsValues(const ProgramOptions* options);
void setDefaultSettings(ProgramOptions* options);
void setUserSettings(ProgramOptions* options);
void showSettingsMenu();
void showMenu();

#endif