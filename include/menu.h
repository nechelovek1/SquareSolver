/*!
    \file
    \brief Библиотека для отображения меню
*/
#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

const int MAX_STR_LEN = 100;

/*!
    \brief структура для хранения настроек программы
    \param inputFilename имя файла для ввода данных
    \param outputFilename имя файла для вывода данных
    \param showComplexRoots флаг отвечающий за отображения комплексных корней
    \param useComplexEnter флаг отвечающий за комплексный ввод
    \param showHelp флаг отвечающий за отображение помощи
    \param useParseEquation флаг 
*/
typedef struct {
    char inputFilename[MAX_STR_LEN];
    char outputFilename[MAX_STR_LEN];
    char bmpName[MAX_STR_LEN];
    bool showComplexRoots;
    bool useComplexEnter;
    bool showHelp;
    bool useParseEquation;
    bool drawGraph;
} ProgramOptions;

typedef struct {
    char menuCode;
    const char* menuString;
} MenuPoint;

/*!
    Ошибки парсера
    \param PARSE_OK ошибок нет
    \param PARSE_MISSING_ARG пропущен обязательный аргумент командной строки
    \param PARSE_UNKNOWN_OPT неизвестная опция командной строки
    \param PARSE_OPTIONS_NULL передан нулевой указатель на ProgramOptions
*/
typedef enum {
    PARSE_OK,
    PARSE_MISSING_ARG,
    PARSE_UNKNOWN_OPT,
    PARSE_OPTIONS_NULL,
} ParseError;


/*!
    \brief Отображает настройки программы
    \param[in] - указатель на структуру настроек
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка 

*/
int showSettingsValues(const ProgramOptions* options);

/*!
    \brief Устанавливает настройки программы по умолчанию
    \param[out] - указатель на структуру для сохранения настроек
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка 
*/
int setDefaultSettings(ProgramOptions* options);

/*!
    \brief Считывает и сохранеят настройки программы, указанные пользователем
    \param[out] options указательна стрруктуру для сохранения настроек
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка 
*/
int setUserSettings(ProgramOptions* options);

/*!
    \brief Отображает меню настроек программы
*/
void showSettingsMenu();

/*!
    \brief Отображает главное меню
*/
void showMenu();

/*!
    \brief Выводит помощь по аргументам командной строки
*/
void printHelpConsole();

/*! 
    \brief Парсит опции командной строки
    \param[in] argc колличество аргументов командной строки (аргумент main)
    \param[in] argv аргументы командной строки (аргумент main)
    \param[out] options указатель на структуру для хранения настроек программы, полученных в результате парсинга
    \return ParseError - ошибки парсера
*/
ParseError parseArgs(int argc, char* argv[], ProgramOptions* options);

#endif