#include "CMakeProject_AISD.h"


using namespace std;

class Element {
	short width_ = 0, height_ = 0;
	char weight_ = '0';
public:
	Element(short width, short height, char weight) {
		width_ = width;
		height_ = height;
		weight_ = weight;
		
	}
	Element(short width, short height) {
		width_ = width;
		height_ = height;
	}

	Element(): width_(0), height_(0) {}

	char get_weight() const {
		return weight_;
	}
	void set_weight(char weight) {
		weight_ = weight;
	}
	short get_height() const {
		return height_;
	}
	short get_width() const {
		return width_;
	}
};

class Grayscale_Image {
	Element** list_elemenst;
	bool feel_;
public:

	Grayscale_Image(short widht, short height, bool feel) {
		list_elemenst = new Element*[widht];
		feel_ = feel;
		if (feel) {
			for (int i = 0; i < widht; i++) {
				list_elemenst[i] = new Element[height];
				for (int j = 0; j < height; j++) {
					list_elemenst[i][j] = Element(i, j, '3');
				}
			}
		}
		else {
			for (int i = 0; i < widht; i++) {
				list_elemenst[i] = new Element[height];
				for (int j = 0; j < height; j++) {
					list_elemenst[i][j] = Element(i, j, '0');
				}
			}
		}
	}

	Element operator()(short x, short y) {
		return list_elemenst[x][y];
	}
};


int main()
{
	srand(time(0));
	Grayscale_Image a(200, 300, true), b(200, 300, false);
	cout << a(3, 5).get_weight() << ' ' << b(50, 200).get_weight() << endl;
	cout << "Hello CMake." << endl;
	return 0;
}
