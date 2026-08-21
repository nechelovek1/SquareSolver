#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "solvers.h"

const int MAX_STR_LEN = 100;

typedef enum {
    PARSE_OK,
    PARSE_MISSING_ARG,
    PARSE_UNEXCEPTED_ARG
} ParseError;

void fPrintRoots(FILE*, RootsCnt, double, double);
ParseError argParse(int, const char*[], char*, char*);
int fGetFirstChar(FILE*);
void fClearInputBuffer(FILE*);
FILE * fOpenDefault(const char*, const char*, FILE*);

int main(int argc, const char* argv[])
{
    char inputFilename[MAX_STR_LEN] = "", outputFilename[MAX_STR_LEN] = "";
    FILE * input = NULL;
    FILE * output = NULL;

    ParseError parseRes = argParse(argc, argv, inputFilename, outputFilename);
    if (parseRes) {
        return -1;
    }
    
    printf("Программа для решения квадратных уравнений\n");

    printf("Ввод:\n");
    input = fOpenDefault(inputFilename, "r", stdin);
    if (input == NULL) {
        return -1;
    }

    printf("Вывод:\n");
    output = fOpenDefault(outputFilename, "w", stdout);
        if (output == NULL) {
        return -1;
    }

    while(1)
    {
        double a = 0, b = 0, c = 0;
        
        if (input == stdin) {
            fprintf(stdout, "Введите коэффициенты a, b, c уравнения ax^2+bx+c=0 (Ctrl + D для завершения)\n");
        }

        int scanfRes = fscanf(input, "%lg %lg %lg ", &a, &b, &c);
        if (scanfRes == EOF) {
            break;
        } else if (scanfRes != 3) {
            fprintf(output, "Ошибка ввода\n");
            fClearInputBuffer(input);
            continue;
        }
        fClearInputBuffer(input);

        double x1 = 0, x2 = 0;
        RootsCnt rootsCnt = solveSquare(a, b, c, &x1, &x2);
        
        fPrintRoots(output, rootsCnt, x1, x2);
    }

    if (output != stdout) {
        fclose(output);
    }
    if (input != stdin) {
        fclose(input);
    }

    printf("Завершено\n");

    return 0;
}

void fPrintRoots(FILE * fp, RootsCnt rootsCnt, double x1, double x2)
{
    switch(rootsCnt) {
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

ParseError argParse(int argc, const char* argv[], char* input, char* output)
{
    int idx = 1;

    while(idx < argc)
    {
        if(!strcmp(argv[idx], "-i") || !strcmp(argv[idx], "-I")){
            if (idx + 1 < argc) {
                strncpy(input, argv[idx + 1], strlen(argv[idx + 1]));
                idx += 2;
            } else {
                fprintf(stderr, "Missing argument -i <input filename>\n");
                return PARSE_MISSING_ARG;
            }
        } else if(!strcmp(argv[idx], "-o") || !strcmp(argv[idx], "-O")){
            if (idx + 1 < argc) {
                strncpy(output, argv[idx + 1], strlen(argv[idx + 1]));
                idx += 2;
            } else {
                fprintf(stderr, "Missing argument -o <output filename>\n");
                return PARSE_MISSING_ARG;
            }
        } else {
            fprintf(stderr, "Unexcepted argument %s\n", argv[idx]);
            return PARSE_UNEXCEPTED_ARG;
        }
    }

    return PARSE_OK;
}

int fGetFirstChar(FILE* fp)
{
    int ch = fgetc(fp);

    while (fgetc(fp) != '\n')
    {
        continue;
    }

    return ch;
}

void fClearInputBuffer(FILE* fp)
{
    int ch = fgetc(fp);

    while (ch != '\n' && ch != EOF)
    {
        ch = fgetc(fp);
        continue;
    }
}

FILE * fOpenDefault(const char* filename, const char* mode, FILE* def)
{
    FILE * fp = NULL;

    if (strlen(filename) == 0) {
        fp = def;
        fprintf(stdout, "Используется стандартный поток\n");
    } else if ((fp = fopen(filename, mode)) == NULL){
        fprintf(stderr, "Не удалось открыть файл %s\n", filename);
    } else {
        fprintf(stdout, "Используется %s\n", filename);
    }

    return fp;
}
