#pragma once
#include <iostream>
#include <ctime>
#include <execution>
#include <random>

namespace space_class {
    template<typename T>
    class GrayscaleImage {
        T* list_elements;
        short width, height;
    public:
        GrayscaleImage();
        GrayscaleImage(short w, short h, bool fill);
        GrayscaleImage(const GrayscaleImage<T>& other);
        void Swap(GrayscaleImage<T>& other);
        GrayscaleImage<T>& operator=(const GrayscaleImage<T>& other);
        T& operator()(short x, short y);
        const T& operator()(short x, short y) const;
        GrayscaleImage<T> operator*(T a);
        GrayscaleImage<T> operator&(bool a);
        GrayscaleImage<T> operator+(T a);
        GrayscaleImage<T> operator|(bool a);
        GrayscaleImage<T> operator!();
        float getFillCoefficient() const;
        void print() const;
        void invert_under_line(short x1, short y1, short x2, short y2) const;
        ~GrayscaleImage();
    };
};


/*
Класс полутоновых изображений произвольного размера.
Типы данных, с которыми должен работать класс.
bool
char
float
short
Как минимум, предоставить:
• конструктор с параметрами: размеры изображения и флагом(True - матрица заполняется случайными значениями выбранного типа/ False – матрица заполняется нулями);
• оператор () для чтения/записи элемента по указанным индексам;
• ? операторы умножения * (поэлементное «И» для bool) и сложения + (поэлементное «ИЛИ» для bool) изображений;
• операторы умножения * и сложения + изображения на константу;
• оператор ! для инвертирования значений изображения(значение меняется на противоположное по модулю);
• вычисление коэффициента заполнения изображения(сумма значений матрицы/ (количество ячеек*максимальное значение заданного типа);

Инвертируйте все значения выше прямой, заданной парой координат (x1,y1)	и (x2,y2)
*/

















