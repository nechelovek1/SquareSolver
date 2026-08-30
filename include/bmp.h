/*!
    \file
    \brief Библиотека для раблты с bmp файлами
*/
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

/*!
    Открывает bmp файл
    \param[in] filename имя файла
    \param[out] bmpOptions указатель на структуру параметров файла
    \param[in] width ширина изображения
    \param[in] height высота изображения
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка 
*/
int openBmp(const char* filename, BmpOptions* fileOptions, unsigned int width, unsigned int height);

/*!
    Задаёт цвет отрисовки
    \param[out] fileOptions указатель на структуру параметров файла
    \param[in] color цвет
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка 
*/
int setColorBmp(BmpOptions* fileOptions, RGB color);

/*!
    Изменяет цвет пикселя
    \param[out] fileOptions указатель на структуру параметров файла
    \param[in] u координата пикселя по ширине
    \param[in] v координата пикселя по высоте
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка 
*/
int drawPixel(BmpOptions* fileOptions, unsigned int u, unsigned int v);

/*!
    Записывает растр в файл
    \param[in] fileOptions указательна структуру параметров файла
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка 
*/
int writeBitmapBmp(BmpOptions* fileOptions);

/*!
    Закрывает bmp файл
    \param[in] fileOptions указательна структуру параметров файла
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка    
*/
int closeBmp(BmpOptions* fileOptions);

/*!
    Отрисовывает оси координат
    \param[out] fileOptions указатель на структуру параметров файла
    \param[in] graphOptions указател на структуру параметров графика
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка    
*/
int drawAxes(BmpOptions* fileOptions, GraphOptions* graphOptions);

/*!
    Отрисовывает ось X
    \param[out] fileOptions указатель на структуру параметров файла
    \param[in] v координата оси по высоте
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка  
*/
int drawAxisX(BmpOptions* fileOptions, unsigned int v);

/*!
    Отрисовывает ось Y
    \param[out] fileOptions указатель на структуру параметров файла
    \param[in] u координата оси по высоте
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка  
*/
int drawAxisY(BmpOptions* fileOptions, unsigned int u);

/*!
    Отрисовывает уравнение вида многочлена на
    \param[out] fileOptions указатель на структуру параметров файла
    \param[in] graphOptions указател на структуру параметров графика
    \param[in] coefs массив коэффициентов
    \param[in] coefsCnt колличество коэффициентов (степень многочлена + 1)
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка      
*/
int drawPolynom(BmpOptions* fileOptions, GraphOptions* graphOptions, const double coefs[], unsigned int coefsCnt);

/*!
    Отрисовывает сетку 
    \param[out] fileOptions указатель на структуру параметров файла
    \param[in] graphOptions указател на структуру параметров графика
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка        
*/
int drawGrid(BmpOptions* fileOptions, GraphOptions* graphOptions);

/*!
    Отрисовыает точку  в системе координат изображения
    \param[out] fileOptions указатель на структуру параметров файла
    \param[in] graphOptions указател на структуру параметров графика
    \param[in] u координата точки по высоте
    \param[in] v координата точки по ширине
    \param[in] r радиус точки
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка    
*/
int drawPoint(BmpOptions* fileOptions, unsigned int u, unsigned int v, unsigned short int r);

/*!
    Отрисовыает точку в системе координат графика
    \param[out] fileOptions указатель на структуру параметров файла
    \param[in] graphOptions указател на структуру параметров графика
    \param[in] x x-координата точки в системе координат графика
    \param[in] y y-координата точки в системе координат графика
    \return 0 - функция выполнилась без ошибок, -1 - в результате выполнения функции произошла ошибка    
*/
int drawGraphPoint(BmpOptions* fileOptions, GraphOptions* graphOptions, double x, double y);

#endif