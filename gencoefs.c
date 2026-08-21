#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CNT 1000

int main()
{
    FILE * fp = fopen("input.txt", "w");
    srand(time(NULL));
    for (int i = 0; i < MAX_CNT; i ++) {
        double a = rand() % 1000 - 500; 
        double b = rand() % 1000 - 500; 
        double c = rand() % 1000 - 500;
        fprintf(fp, "%lg %lg %lg\n", a, b, c); 
    }
    fclose(fp);

}