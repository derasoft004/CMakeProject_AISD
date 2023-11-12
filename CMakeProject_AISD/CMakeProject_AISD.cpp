#include "CMakeProject_AISD.h"
#define w_space 4

using namespace std;
using namespace space_class;

template<typename T>
GrayscaleImage<T>::GrayscaleImage() : list_elements(nullptr), width(0), height(0) {}

template<typename T>
GrayscaleImage<T>::GrayscaleImage(short w, short h, bool fill) : width(w), height(h) {
	srand(time(0));
	list_elements = new T[w * h];
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 9); // случайный Т от 0 до макс numeric_limits<T>::max()
	for (int i = 0; i < width * height; i++) {
		for (int j = 0; j < height; j++) {
			if (fill) list_elements[i * width + j] = dis(gen);
			else list_elements[i * width + j] = 0;
		}
	}
}

template<typename T>
GrayscaleImage<T>::GrayscaleImage(const GrayscaleImage<T>& other) {
	this->list_elements = other.list_elements;
	this->width = other.width;
	this->height = other.height;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			list_elements[i * width + j] = other.list_elements[i * width + j];
		}
	}
}

template<typename T>
void GrayscaleImage<T>::Swap(GrayscaleImage<T>& other) {
	swap(this->list_elements, other.list_elements);
	swap(this->width, other.width);
	swap(this->height, other.height);
}

template<typename T>
GrayscaleImage<T>& GrayscaleImage<T>::operator=(const GrayscaleImage<T>& other) {
	GrayscaleImage copy(other);
	this->Swap(copy);
	return *this;
}

template<typename T>
T& GrayscaleImage<T>::operator()(short x, short y) { // оператор на запись
	if (x >= 0 && x < width && y >= 0 && y < height)
		return list_elements[x * width + y];
	else throw "Index out of range!";
}

template<typename T>
const T& GrayscaleImage<T>::operator()(short x, short y) const { // чтиво
	if (x >= 0 && x < width && y >= 0 && y < height)
		return list_elements[x * width + y];
	else throw "Index out of range!";
}

template<typename T>
GrayscaleImage<T> GrayscaleImage<T>::operator*(T a) {
	GrayscaleImage<T> other(width, height, false);
	for (int i = 0; i < width * height; i++) {
		other.list_elements[i] = list_elements[i] * a;
	}
	return other;
}


template<typename T>
GrayscaleImage<T> GrayscaleImage<T>::operator+(T a) {
	GrayscaleImage<T> other(width, height, false);
	for (int i = 0; i < width * height; i++) {
		other.list_elements[i] = list_elements[i] + a;
	}
	return other;
}


/*
GrayscaleImage<T> operator*(T a) const {

	for (int i = 0; i < width * height; i++) {
		list_elements[i] *= a;
	}
	return *this;
}

GrayscaleImage<T> operator+(T a) {
	for (int i = 0; i < width * height; i++) {
		list_elements[i] += a;
	}
	return *this;
} - так выдает ошибку кучи _CrtlsValidHeapPointer
*/

template<typename T>
GrayscaleImage<T> GrayscaleImage<T>::operator!() { // как поменять на void и менять непосредственно в объекте
	GrayscaleImage<T> other(width, height, false);
	for (int i = 0; i < width * height; i++) {
		if (typeid(T).name() == typeid(bool).name()) other.list_elements[i] = !list_elements[i];
		else if (typeid(T).name() == typeid(char).name()) other.list_elements[i] = list_elements[i];
		else other.list_elements[i] = !list_elements[i] + 1;
	}
	return other;
}

template<typename T>
float GrayscaleImage<T>::getFillCoefficient() const {
	float sum = 0;
	if (typeid(T).name() != typeid(bool).name() && typeid(T).name() != typeid(char).name()) {
		for (int i = 0; i < width * height; i++) {
			sum += list_elements[i];
		}
	}
	return sum / (width * height);
}

template<typename T>
void GrayscaleImage<T>::print() const {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			cout.width(w_space);
			cout << list_elements[i * width + j] << " ";
		}
		cout << endl;
	}
}

template<typename T>
void GrayscaleImage<T>::invert_under_line(short x1, short y1, short x2, short y2) const {
	if (x1 == x2 && y1 == y2) {
		cout << "enter two different points" << endl;
		return;
	}
	else if (x1 >= width || x2 >= width || y1 >= height || y2 >= height) {
		cout << "enter points with (x, y), into the matrix" << endl;
		return;
	}
	else if (x1 == x2) {
		cout << "enter points with not vertical line" << endl;
		return;
	}
	else if ((x1 == x2 && y1 == y2) || (x1 >= width || x2 >= width || y1 >= height || y2 >= height)) {
		cout << "enter points for straight or oblique" << endl; // прямая или косая
		return;
	}

	int type = 0;
	if ((y1 == y2) && (x1 != x2)) {
		type = 1;
	}
	else if ((x1 < x2 && y1 > y2) || (x1 > x2 && y1 < y2)) {
		if ((x1 > x2 && y1 < y2)) {
			short tmpx = x2, tmpy = y2;
			x2 = x1;
			x1 = tmpx;
			y2 = y1;
			y1 = tmpy;

		}
		type = 2;
		while ((y1 < height - 1 && x1 > 0) || (x2 < width - 1 && y2 > 0)) {
			// cout << x1 << y1 << x2 << y2 << endl; // для отладки
			if (x2 < width - 1) {
				x2 += 1;
				y2 -= 1;
			}
			if (y1 < height - 1) {
				x1 -= 1;
				y1 += 1;
			}
			// cout << "=>" << x1 << y1 << x2 << y2 << endl; // для отладки
		}
	}
	else if (x1 > x2 && y1 < y2) {
		type = 3;
	}

	short tmpx1 = x1, tmpy1 = y1, tmpx2 = x2, tmpy2 = y2;
	int path = 0;
	for (int i = 0; i < width; i++) {
		if (type == 2) {
			if (i < y2) path = 1;
			else path = 0;
		}
		for (int j = 0; j < height; j++) {
			if (type == 1) { // горизонтальная линия, полностью работает
				if (i < y1) {
					if (list_elements[i * width + j] > 0) list_elements[i * width + j] = !list_elements[i * width + j] + 1;
				}
				else {
					if (list_elements[i * width + j] < 0) list_elements[i * width + j] = !list_elements[i * width + j] + 1;
				}
			}

			if (type == 2) {
				if ((tmpx1 < tmpx2 && tmpy1 > tmpy2) || (tmpx1 == tmpx2 && tmpy1 == tmpy2)) {
					if (path) {
						if (list_elements[i * width + j] > 0) list_elements[i * width + j] = !list_elements[i * width + j] + 1;
					}
					else if (!path) {
						if (j < tmpx2 && i <= tmpy1 && i + j < tmpx1 + tmpy1) {
							if (list_elements[i * width + j] > 0) list_elements[i * width + j] = !list_elements[i * width + j] + 1;
						}
						else {
							if (list_elements[i * width + j] < 0) list_elements[i * width + j] = !list_elements[i * width + j] + 1;
						}
					}
				}
			}
		}
		cout << endl;
	}
}

template<typename T>
GrayscaleImage<T>::~GrayscaleImage() {
	delete[] list_elements;
}

