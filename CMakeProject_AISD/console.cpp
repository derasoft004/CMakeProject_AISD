#include "CMakeProject_AISD.cpp"

using namespace space_class;
int main()
{
    short a1 = 5, a2 = 5, a3 = 5, a4 = 5;
    short b1 = 5, b2 = 5, b3 = 5, b4 = 5;
    bool z1 = 1, z2 = 1, z3 = 1, z4 = 1;

    cout << "image with short filling" << endl;
    GrayscaleImage<short> image1(a1, b1, z1);
    cout << image1;

    cout << "image with bool filling" << endl;
    GrayscaleImage<bool> image2(a2, b2, z2);
    cout << image2;

    cout << "image with char filling" << endl;
    GrayscaleImage<char> image3(a3, b3, z3);
    cout << image3;

    cout << "image with float filling" << endl;
    GrayscaleImage<float> image4(a4, b4, z4, 1);
    cout << image4;

    try {
        cout << "invert image1 under line (1, 1)(2, 1)" << endl;
        image1.invert_under_line(1, 1, 2, 1);
        cout << image1;

        cout << "invert image4 under line (0, 3)(3, 0)" << endl;
        image4.invert_under_line(0, 3, 3, 0);
        cout << image4;

        cout << "invert image3 under line (2, 4)(4, 2) - error, this is image with char filling" << endl;
        image3.invert_under_line(2, 4, 4, 2);
        cout << image3;
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }


    try {
        cout << "invert image1" << endl;
        !image1;
        cout << image1;
        cout << "invert image2" << endl;
        !image2;
        cout << image2;
        cout << "invert image4" << endl;
        !image4;
        cout << image4;
        cout << "invert image3 - error, this is image with char filling" << endl;
        !image3;
        cout << image3;

    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    try {
        cout << "elem (0, 2) in image1" << endl;
        cout << image1(2, 0) << endl;
        cout << "elem (0, 5) in image1 - error, index out of range (0-4)" << endl;
        cout << image1(0, 5) << endl;
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
    try {
        GrayscaleImage<short> image11(a1, b1, z1);
        auto image12 = image11;
        cout << (image11 == image12) << endl;
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }


}