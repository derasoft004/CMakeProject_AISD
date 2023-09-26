#include "CMakeProject_AISD.h"


using namespace std;


template<typename T>
class GrayscaleImage {
	T* list_elements;
	int width, height;
public:

	GrayscaleImage(int w, int h, bool feel): width(w), height(h) {
		srand(time(0));
		list_elements = new T[width * height];
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, 10); // случайный Т от 0 до макс numeric_limits<T>::max()
		for (int i = 0; i < width * height; i++) {
			if (feel) list_elements[i] = dis(gen);
			else list_elements[i] = 0;
		}
	}

	T& operator()(int x, int y) { // оператор на запись
		if (x >= 0 && x < width && y >= 0 && y < height) 
			return list_elements[x * width + y];
		else throw "Index out of range!";
	}

	const T& operator()(int x, int y) const { // чтиво
		if (x >= 0 && x < width && y >= 0 && y < height)
			return list_elements[x * width + y];
		else throw "Index out of range!";
	}

	GrayscaleImage<T> operator*(T a) const {
		GrayscaleImage<T> other(width, height, false);
		for (int i = 0; i < width * height; i++) {
			other.list_elements[i] = list_elements[i] * a;
		}
		return other;
	}

	GrayscaleImage<T> operator+(T a) {
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

	GrayscaleImage<T> operator!(){
		GrayscaleImage<T> other(width, height, false);
		for (int i = 0; i < width * height; i++) {
			other.list_elements[i] = ~list_elements[i] + 1;
		}
		return other;
	}

	float getFillCoefficient() const {
		float sum = 0;
		for (int i = 0; i < width * height; i++) {
			sum += list_elements[i];
		}
		return sum / (width * height);
	}

	void print() const {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << list_elements[i * width + j] << " ";
			}
			cout << endl;
		}
	}

	~GrayscaleImage() {
		delete[] list_elements;
	}
};	


int main()
{
	setlocale(LC_ALL, "");
	GrayscaleImage<int> image(3, 3, true);
	image.print(); // принтанули

	cout << "изменим 2-ой элемент на 11" << endl;
	image(0, 1) = 11; // изменили
	image.print();

	GrayscaleImage<int> image_addition = image + 10;
	cout << "прибавили 10" << endl;
	image_addition.print(); // прибавили 10 

	GrayscaleImage<int> inverted_image = !image_addition;
	cout << "инвертируем" << endl;
	inverted_image.print(); // инвертировали

	GrayscaleImage<int> image_composition = inverted_image * 2;
	cout << "умножим все на 2" << endl;
	image_composition.print(); // умножили на 2 принтанули

	cout << "пустая матрица" << endl;
	GrayscaleImage<int> empty_image(3, 3, false);
	empty_image.print();

	float fillCoefficient = image.getFillCoefficient();
	cout << "Fill coefficient: " << fillCoefficient << endl;

	
	return 0;
}
