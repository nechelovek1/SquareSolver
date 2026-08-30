#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main()
{
    BmpOptions fileOptions = {};

    unsigned short int height = 1920;
    unsigned short int width = 1080;

    openBmp("test1.bmp", &fileOptions, height, width);

    GraphOptions graphOptions = {.centerX = 1000, .centerY = 500, .pixelsPerUnit = 25, .samplesPerPixel = 10000};

    setColorBmp(&fileOptions, (RGB){.b=0x80, .g=0x80, .r=0x80});    
    drawGrid(&fileOptions, &graphOptions);

    setColorBmp(&fileOptions, (RGB){.b=0xff, .g=0xff, .r=0xff});    
    drawAxes(&fileOptions, &graphOptions);

    const int coefsCnt = 3;
    double coefs[coefsCnt] = {-2, 1, 1};

    setColorBmp(&fileOptions, (RGB){.b = 0x00, .g = 0xff, .r = 0xff});
    drawPolynom(&fileOptions, &graphOptions, coefs, coefsCnt);

    setColorBmp(&fileOptions, (RGB){.b = 0xff, .g = 0x00, .r = 0x00});
    drawGraphPoint(&fileOptions, &graphOptions, 1, 0);
    drawGraphPoint(&fileOptions, &graphOptions, -2, 0);


    writeBitmapBmp(&fileOptions);
    closeBmp(&fileOptions);

    return 0;
}