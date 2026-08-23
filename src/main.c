#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#include "solvers.h"
#include "menu.h"

const double EPS = 1e-10;

typedef enum {
    PARSE_OK,
    PARSE_MISSING_ARG,
    PARSE_UNKNOWN_OPT,
} ParseError;

/*
    Выводит корни в файл.
    Принимает на вход
        FILE* fp          - указатель на файл
        RootsCnt rootsCnt - количество корней
        double x1         - первый корень
        double x2         - второй корень
    Возвращает
*/
void fPrintRoots(FILE* fp, RootsCnt rootsCnt, double x1, double x2);
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
int fGetFirstChar(FILE*);
/*

*/
FILE * fOpenDefault(const char*, const char*, FILE*);
int solveSquareInLoop(const ProgramOptions* options);
int fGetComplex(FILE* fp, _Complex double* c);
void fPrintComplex(FILE* fp, _Complex double c);
void fPrintRootsComplex(FILE* fp, RootsCnt rootsCnt, _Complex double x1, _Complex double x2);


int main(int argc, char* argv[])
{
    ProgramOptions options = {.inputFilename = "", .outputFilename = ""};

    ParseError parseRes = parseArgs(argc, argv, &options);
    if (parseRes) {
        return -1;
    }

    printf("Program for solving quadratic equations\n");
    
    showSettingsValues(&options);
    solveSquareInLoop(&options);

    int choice = ' ';

    while (choice != EOF && choice != 'e') {

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
                solveSquareInLoop(&options);
                break;
            default:
                printf("Unknown\n");
        }
        
    }

    printf("Done\n");

    return 0;
}

void fPrintRoots(FILE* fp, RootsCnt rootsCnt, double x1, double x2)
{
    switch(rootsCnt)
    {
        case ZERO_ROOTS:
            fprintf(fp, "Действительных корней нет\n\n");
            break;
        case ONE_ROOTS:
            fprintf(fp, "x=%.3lg\n\n", x1);
            break;
        case TWO_ROOTS:
            fprintf(fp, "x1=%.3lg x2=%.3lg\n\n", x1, x2);
            break;
        case INF_ROOTS:
            fprintf(fp, "Корнем явялется любое число\n\n");
            break;
        case ERR_ROOTS:
            fprintf(fp, "Решение квадратного уравнения завершилось с ошибкой\n\n");
            break;
        default:
            fprintf(fp, "Неожиданное значение\n\n");
    }
}

void fPrintRootsComplex(FILE* fp, RootsCnt rootsCnt, _Complex double x1, _Complex double x2)
{
    switch(rootsCnt)
    {
        case ZERO_ROOTS:
            fprintf(fp, "Корней нет\n\n");
            break;
        case ONE_ROOTS:
            printf("x1=");
            fPrintComplex(fp, x1);
            fprintf(fp, "\n\n");
            break;
        case TWO_ROOTS:
            fprintf(fp, "x1=");
            fPrintComplex(fp, x1);
            fprintf(fp, " x2=");
            fPrintComplex(fp, x2);
            fprintf(fp, "\n\n");
            break;
        case INF_ROOTS:
            fprintf(fp, "Корнем явялется любое число\n\n");
            break;
        case ERR_ROOTS:
            fprintf(fp, "Решение квадратного уравнения завершилось с ошибкой\n\n");
            break;
        default:
            fprintf(fp, "Неожиданное значение\n\n");
    }
}

ParseError parseArgs(int argc, char* argv[], ProgramOptions* options)
{
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

FILE* fOpenDefault(const char* filename, const char* mode, FILE* def)
{
    FILE* fp = NULL;

    if (strlen(filename) == 0) {
        fp = def;
    } else if ((fp = fopen(filename, mode)) == NULL){
        fprintf(stderr, "Не удалось открыть файл %s\n", filename);
    }

    return fp;
}

int solveSquareInLoop(const ProgramOptions* options)
{
    FILE* input = NULL;
    FILE* output = NULL;

    input = fOpenDefault(options->inputFilename, "r", stdin);
    if (input == NULL) {
        return -1;
    }
    output = fOpenDefault(options->outputFilename, "w", stdout);
        if (output == NULL) {
        return -1;
    }

    while(true)
    {
        double a = 0, b = 0, c = 0;

        if (input == stdin) {
            printf("Enter e for exit and any char for continue: ");

            int choice = getchar();
            fClearInputBuffer(input);

            if (tolower(choice) == 'e') {
                break;
            }

            printf("Введите коэффициенты a, b, c уравнения ax^2+bx+c=0 (e для завершения)\n");
        }
        
        int scanfRes = fscanf(input, "%lg %lg %lg", &a, &b, &c);
        if (scanfRes == EOF) {
            break;
        } else if (scanfRes != 3) {
            fprintf(output, "Ошибка ввода\n");
            fClearInputBuffer(input);
            continue;
        }
        fClearInputBuffer(input);

        if (options->useComplexEnter || options->showComplexRoots) {
            _Complex double x1 = 0, x2 = 0;
            RootsCnt rootsCnt = solveSquareComplex(a, b, c, &x1, &x2);
            fPrintRootsComplex(output, rootsCnt, x1, x2);
        } else {
            double x1 = 0, x2 = 0;
            RootsCnt rootsCnt = solveSquare(a, b, c, &x1, &x2);
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

//TODO доделать функцию чтения комплексного числа
int fGetComplex(FILE* fp, _Complex double* c)
{
    double im = 0.0, re = 0.0;
    int n = 0;

    int scanfRes = fscanf(fp, "%lg+%lg", &re, &im);
    fscanf(fp, "i%n", &n);

    if (n != 1 || scanfRes != 2) {
        return 0;
    } else {
        *c = re + im * I;
    }

    return 1;
}

void fPrintComplex(FILE* fp, _Complex double c)
{
    if (isequal(cimag(c), 0, EPS)) {
        fprintf(fp, "%lg", creal(c));
    } else if (isequal(creal(c), 0, EPS)) {
        fprintf(fp, "%lgi", cimag(c));
    }else {
        fprintf(fp, "%lg+%lgi", creal(c), cimag(c));
    }
}