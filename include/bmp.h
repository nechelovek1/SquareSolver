#ifndef BMP_H
#define BMP_H

#include <stdio.h>

#define BMP_MAGIC 0x4d42

#pragma pack(push, 1)
typedef struct {
    unsigned short int bfType;
    unsigned int bfSize;
    unsigned short int bfReserved1;
    unsigned short int bfReserved2;
    unsigned int bfOffBits;
} BITMAPFILEHEADER;
#pragma pack(pop)

typedef struct {
    unsigned int biSize;
    unsigned int biWidth;
    unsigned int biHeight;
    unsigned short int biPlanes;
    unsigned short int biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    unsigned int biXPelsPerMeter;
    unsigned int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BITMAPINFOHEADER;

typedef struct {
    unsigned char b, g, r;
} RGB;

const RGB BMP_BLACK   = {.b = 0x00, .g = 0x00, .r = 0xff};
const RGB BMP_WHITE   = {.b = 0xff, .g = 0xff, .r = 0xff};
const RGB BMP_RED     = {.b = 0x00, .g = 0x00, .r = 0xff};
const RGB BMP_GREEN   = {.b = 0x00, .g = 0xff, .r = 0x00};
const RGB BMP_BLUE    = {.b = 0xff, .g = 0x00, .r = 0x00};
const RGB BMP_YELLOW  = {.b = 0x00, .g = 0xff, .r = 0xff};
const RGB BMP_PINK    = {.b = 0xff, .g = 0x00, .r = 0xff};
const RGB BMP_CYAN    = {.b = 0xff, .g = 0xff, .r = 0x00};
const RGB BMP_GREY    = {.b = 0x80, .g = 0x80, .r = 0x80};


typedef struct {
    unsigned int width;
    unsigned int height; 
    //unsigned short int bitsPerPixel;  
    FILE* bmpFile;
    RGB color;
    RGB* bitmap;
} BmpOptions;

typedef struct {
    unsigned short int centerX;
    unsigned short int centerY;
    unsigned short int pixelsPerUnit;
    unsigned int samplesPerPixel;
} GraphOptions;

int openBmp(const char* filename, BmpOptions* fileOptions, unsigned int width, unsigned int height);
int setColorBmp(BmpOptions* fileOptions, RGB color);
int drawPixel(BmpOptions* fileOptions, unsigned int u, unsigned int v);
int writeBitmapBmp(BmpOptions* fileOptions);
int closeBmp(BmpOptions* fileOptions);

int drawAxes(BmpOptions* fileOptions, GraphOptions* graphOptions);
int drawAxisX(BmpOptions* fileOptions, unsigned int v);
int drawAxisY(BmpOptions* fileOptions, unsigned int u);
int drawPolynom(BmpOptions* fileOptions, GraphOptions* graphOptions, const double coefs[], unsigned int coefsCnt);
int drawGrid(BmpOptions* fileOptions, GraphOptions* graphOptions);
int drawPoint(BmpOptions* fileOptions, unsigned int u, unsigned int v, unsigned short int r);
int drawGraphPoint(BmpOptions* fileOptions, GraphOptions* graphOptions, double x, double y);

#endif