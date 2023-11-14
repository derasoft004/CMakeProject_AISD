#include "CMakeProject_AISD.cpp"

using namespace space_class;
int main()
{
    short a1 = 5, a2 = 5, a3 = 5, a4 = 5;
    short b1 = 5, b2 = 5, b3 = 5, b4 = 5;
    bool z1 = 1, z2 = 1, z3 = 1, z4 = 1;

    GrayscaleImage<short> image1(a1, b1, z1);
    cout << image1;

    GrayscaleImage<bool> image2(a2, b2, z2);
    cout << image2;

    GrayscaleImage<char> image3(a3, b3, z3);
    cout << image3;

    GrayscaleImage<float> image4(a4, b4, z4, 1);
    cout << image4;

    try {
        !image1;
        cout << image1;
        !image2;
        cout << image2;
        !image4;
        cout << image4;
        !image3;
        cout << image3;

    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}