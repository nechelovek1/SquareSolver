#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "bmp.h"


double calcPolynom(const double coefs[], unsigned int coefsCnt, double x)
{
    double y = 0; double xCur = 1;

    for (unsigned int i = 0; i < coefsCnt; i++)
    {
        y += coefs[i] * xCur;
        xCur *= x;
    }

    return y;
}

int openBmp(const char* filename, BmpOptions* fileOptions, unsigned int width, unsigned int height)
{
    if (fileOptions == NULL) {
        return -1;
    }

    fileOptions->width = width;
    fileOptions->height = height;
    unsigned short int bitsPerPixel = 24;

    unsigned int offset = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    unsigned int size = offset + width * height * bitsPerPixel / 8;

    BITMAPFILEHEADER header = {BMP_MAGIC, size, 0, 0, offset};
    BITMAPINFOHEADER info = {40, fileOptions->width, fileOptions->height, 1, bitsPerPixel, 0, (unsigned int) fileOptions->width * fileOptions->height * bitsPerPixel / 8, 0, 0, 0};
    
    fileOptions->bitmap = (RGB*) calloc(width * height, sizeof(RGB));
    if (fileOptions->bitmap == NULL) {
        return -1;
    }

    fileOptions->bmpFile = fopen(filename, "wb");
    if (fileOptions->bmpFile == NULL)
    {
        return -1;
    }

    fwrite(&header, sizeof(header), 1, fileOptions->bmpFile);
    fwrite(&info, sizeof(info), 1, fileOptions->bmpFile);

    return 0;
}

int setColorBmp(BmpOptions* fileOptions, RGB color)
{   
    if (fileOptions == NULL) {
        return -1;
    }

    fileOptions->color = color;

    return 0;
}

int drawPixel(BmpOptions* fileOptions, unsigned int u, unsigned int v)
{
    if (fileOptions == NULL || fileOptions->bitmap == NULL) {
        return -1;
    }

    if (v > fileOptions->height || u > fileOptions->width) {
        return -1;
    }

    fileOptions->bitmap[v * fileOptions->width + u] = fileOptions->color;

    return 0;
}

int writeBitmapBmp(BmpOptions* fileOptions)
{
    if (fileOptions == NULL || fileOptions->bmpFile == NULL || fileOptions->bitmap == NULL)
    {   
        return -1;
    }

    fwrite(fileOptions->bitmap, sizeof(RGB), fileOptions->width * fileOptions->height, fileOptions->bmpFile);

    return 0;
}

int closeBmp(BmpOptions* fileOptions)
{
    if (fileOptions == NULL || fileOptions->bmpFile == NULL || fileOptions->bitmap == NULL)
    {   
        return -1;
    }

    free(fileOptions->bitmap);
    fclose(fileOptions->bmpFile);

    fileOptions->bmpFile = NULL;
    fileOptions->bitmap = NULL;

    return 0;
}

int drawAxes(BmpOptions* fileOptions, GraphOptions* graphOptions)
{
    if (fileOptions == NULL || graphOptions == NULL) {
        return -1;
    }

    drawAxisX(fileOptions, graphOptions->centerY);
    drawAxisY(fileOptions, graphOptions->centerX);

    return 0;
}

int drawAxisX(BmpOptions* fileOptions, unsigned int v)
{
    if (fileOptions == NULL) {
        return -1;
    }

    for (unsigned int i = 0; i < fileOptions->width; i++)
    {
        drawPixel(fileOptions, i, v);
    }

    return 0;
}

int drawAxisY(BmpOptions* fileOptions, unsigned int u)
{
    if (fileOptions == NULL) {
        return -1;
    }   

    for (unsigned int i = 0; i < fileOptions->height; i++)
    {
        drawPixel(fileOptions, u, i);
    }

    return 0;
}

int drawPolynom(BmpOptions* fileOptions, GraphOptions* graphOptions, const double coefs[], unsigned int coefsCnt)
{
    if (fileOptions == NULL || graphOptions == NULL || coefs == NULL) {
        return -1;
    }

    double minY = (double) (fileOptions->height - graphOptions->centerY) / graphOptions->pixelsPerUnit;
    double maxY = (double) graphOptions->centerY / graphOptions->pixelsPerUnit;
    double minX = (double) -graphOptions->centerX / graphOptions->pixelsPerUnit;

    for (unsigned int i = 0; i < fileOptions->width * graphOptions->samplesPerPixel; i++)
    {
        double y = calcPolynom(coefs, coefsCnt, minX + (double) i / graphOptions->pixelsPerUnit / graphOptions->samplesPerPixel);
        long j = (long) ((y + maxY) * graphOptions->pixelsPerUnit);
        if (0 < j && j < fileOptions->height) {
            drawPixel(fileOptions, i / graphOptions->samplesPerPixel, j);
        }
    }

    return 0;
}

int drawGrid(BmpOptions* fileOptions, GraphOptions* graphOptions)
{
    if (fileOptions == NULL || graphOptions == NULL) {
        return -1;
    }

    for (unsigned int i = graphOptions->centerX % graphOptions->pixelsPerUnit; i < fileOptions->width; i += graphOptions->pixelsPerUnit)
    {
        drawAxisY(fileOptions, i);
    }

    for (unsigned int i = graphOptions->centerY % graphOptions->pixelsPerUnit; i < fileOptions->height; i += graphOptions->pixelsPerUnit)
    {
        drawAxisX(fileOptions, i);
    }

    return 0;
}

int drawPoint(BmpOptions* fileOptions, unsigned int u, unsigned int v, unsigned short int r)
{
    if (fileOptions == NULL) {
        return -1;
    }

    for (int i = -r; i <= r; i++)
    {
        for (int j = -r; j <= r; j++)
        {
            if (i * i + j * j <= r * r){
                drawPixel(fileOptions, u + i, v + j);
            }
        }
    }

    return 0;
}

int drawGraphPoint(BmpOptions* fileOptions, GraphOptions* graphOptions, double x, double y)
{
    if (fileOptions == NULL || graphOptions == NULL) {
        return -1;
    }

    unsigned int u = (unsigned int) (x * graphOptions->pixelsPerUnit + graphOptions->centerX);
    unsigned int v = (unsigned int) (y * graphOptions->pixelsPerUnit + graphOptions->centerY);

    //TODO сделать радиус точки заисисмым от масштаба графика
    unsigned int r = 2;

    drawPoint(fileOptions, u, v, r);

    return 0;
}