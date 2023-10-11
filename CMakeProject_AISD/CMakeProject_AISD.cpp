#include "CMakeProject_AISD.h"
#define w_space 6

using namespace std;


template<typename T>
class GrayscaleImage {
	T* list_elements;
	int width, height;
public:

	GrayscaleImage(int w, int h, bool feel): width(w), height(h) {
		srand(time(0));
		list_elements = new T[w * h];
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
			other.list_elements[i] = ~list_elements[i] + 1; // ~ - побитовое инвертирование, нужно добавлять 1
		}
		return other;
	}

	GrayscaleImage<T> invert_upper_line(T x1, T y1, T x2, T y2) {
		GrayscaleImage<T> other(width, height, false);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (i < y1 && j > x2) {
					other.list_elements[i * width + j] = ~list_elements[i * width + j] + 1;
				}
				else other.list_elements[i * width + j] = list_elements[i * width + j];
			}
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
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				cout.width(w_space);
				cout << list_elements[i * width + j] << " ";
			}
			cout << endl;
		}
	}
	void print_index(T x1, T y1, T x2, T y2) const { // x1 И x2 - j; y1 И y2 - i
		if (x1 == x2 && y1 == y2) {
			cout << "введтите две разные точки" << endl;
			return;
		}
		if (x1 > width || x2 > width || y1 > height | y2 > height) {
			cout << "введите точки с координатами, не выходящими за границы" << endl;
			return;
		}
		if (y1 == y2) {
			cout << "введите точки, для которых линия не будет вертикальной" << endl;
			return;
		}

		int type = 0;
		if ((x1 == x2) && (y1 != y2)) {
			type = 1;
		}
		else if (x1 < x2 && y1 > y2) {
			type = 2;
			while ((y1 < height - 1 && x1 > 0) || (x2 < width - 1 && y2 > 0)) {
				cout << x1 << y1 << x2 << y2 << endl;
				if (x2 < width-1) {
					x2 += 1;
					y2 -= 1;
				}
				if (y1 < height-1) {
					x1 -= 1;
					y1 += 1;
				}
				cout << "=>" << x1 << y1 << x2 << y2 << endl;
			}
		}
		else if (x1 > x2 && y1 < y2) {
			type = 3;
			while ((y1 < height - 1 && x1 > 0) || (x2 < width - 1 && y2 > 0)) {
				cout << x1 << y1 << x2 << y2 << endl;
				if (x2 < width - 1) {
					x2 += 1;
					y2 -= 1;
				}
				if (y1 < height - 1) {
					x1 -= 1;
					y1 += 1;
				}
				cout << "=>" << x1 << y1 << x2 << y2 << endl;
			}
		}

		T tmpx1 = x1, tmpy1 = y1, tmpx2 = x2, tmpy2 = y2;
		int path = 0;
		for (int i = 0; i < width; i++) {
			if (type == 2) {
				if (i < y2) path = 1;
				else path = 0;
			}
			for (int j = 0; j < height; j++) { 
				if (type == 1) { // горизонтальная линия, полностью работает
					if ((i * width + j)/5 < (fabs((x1 * width + y1) / 5))) {
						cout.width(w_space);
						cout << "-" << i << j;
					}
					else {
						cout.width(w_space);
						cout << " " << i << j;
					}
				}

				if (type == 2) {
					if ((tmpx1 < tmpx2 && tmpy1 > tmpy2) || (tmpx1 == tmpx2 && tmpy1 == tmpy2)) {
						if (path) {
							cout.width(w_space);
							cout << "-" << i << j;
						}
						else if (!path) {
							if (j < tmpx2 && i <= tmpy1 && i+j < tmpx1 + tmpy1) {
								cout.width(w_space);
								cout << "-" << i << j;
							}
							else { 
								cout.width(w_space);
								cout << " " << i << j;
							}
						}
					}
				}				
			}
			if (type == 2) {
				
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
	GrayscaleImage<int> image(5, 5, true);
	image.print(); // принтанули
	/*
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
	*/
	GrayscaleImage<int> invert_upper_line = image.invert_upper_line(0, 3, 3, 0);
	cout << "инвертируем все что над прямой 2-ой линией линией" << endl;
	invert_upper_line.print_index(2, 2, 2, 3);
	cout << "инвертируем все что над косой линией (0, 4) (4, 0) линией" << endl;
	invert_upper_line.print_index(2, 3, 3, 2);
	cout << "инвертируем все что над косой линией (2, 3) (4, 1) линией" << endl;
	invert_upper_line.print_index(2, 3, 4, 1);

	

	
	return 0;
}
