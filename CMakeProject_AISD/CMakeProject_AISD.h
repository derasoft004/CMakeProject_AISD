#include <iostream>
#include <ctime>
#include <execution>
#define w_space 4
#include <random>

using namespace std;

namespace space_class {
    template<typename T>
    class GrayscaleImage {
    private:
        T* list_elements;
        short width, height;
    public:
        GrayscaleImage();
        GrayscaleImage(short w, short h, bool fill);
        GrayscaleImage(short w, short h, bool fill, bool is_float);
        GrayscaleImage(const GrayscaleImage<T>& other);
        void Swap(GrayscaleImage<T>& other);
        GrayscaleImage<T>& operator=(const GrayscaleImage<T> other);
        T& operator()(short x, short y);
        const T& operator()(short x, short y) const;
        GrayscaleImage<T> operator*(T a);
        GrayscaleImage<T> operator+(T a);
        bool operator==(const GrayscaleImage<T>& other) const;
        void operator!();
        float getFillCoefficient() const;
        void invert_under_line(short x1, short y1, short x2, short y2) const;
        ~GrayscaleImage();
        friend std::ostream& operator<<(std::ostream& os, const GrayscaleImage<T>& img) {
            for (int i = 0; i < img.width; i++) {
                for (int j = 0; j < img.height; j++) {
                    os << img.list_elements[i * img.width + j] << " ";
                }
                os << '\n';
            }
            return os;
        }
    };


}