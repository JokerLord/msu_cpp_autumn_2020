#include <iostream>
#include <cassert>

class Row
{
private:
	size_t length;
	int *arr;
public:
	Row(int *a, size_t b) : arr(a), length(b) {}
	int& operator[](int i) {
		if ((0 <= i) && (i < length)) {
			return arr[i];
		} else {
			throw std::out_of_range("Ha!");
		}
	}
	const int& operator[](int i) const {
		if ((0 <= i) && (i < length)) {
			return arr[i];
		} else {
			throw std::out_of_range("Ha!");
		}
	}
};

class Matrix
{
private:
	size_t rows;
	size_t cols;
	int **arr;
public:
	Matrix(size_t r = 0, size_t c = 0) : rows(r), cols(c) {
		arr = new int*[rows];
		for (int i = 0; i < rows; ++i) {
			arr[i] = new int[cols];
		}
	}
	Matrix(const Matrix &matr) {
		rows = matr.rows;
		cols = matr.cols;
		arr = new int*[rows];
		for (int i = 0; i < rows; ++i) {
			arr[i] = new int[cols];
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				arr[i][j] = matr[i][j];
			}
		}
	}
	size_t getRows() const {
		return rows;
	}
	size_t getColumns() const {
		return cols;
	}
	Row operator[](size_t i) const {
		if ((0 <= i) && (i < rows)) {
			return Row(arr[i], cols);
		} else {
			throw std::out_of_range("Ha!");
		}
	}
	Matrix& operator=(const Matrix &matr) {
		if (arr != matr.arr) {
			for (int i = 0; i < rows; ++i) {
				delete[] arr[i];
			}
			delete[] arr;
			rows = matr.rows;
			cols = matr.cols;
			arr = new int*[rows];
			for (int i = 0; i < rows; ++i) {
				arr[i] = new int[cols];
			}
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					arr[i][j] = matr[i][j];
				}
			}
		}
		return *this;
	}
	Matrix& operator*=(int value) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				arr[i][j] *= value;
			}
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream &out, const Matrix &matr);

	Matrix operator+(const Matrix &matr) {
		if (rows != matr.rows || cols != matr.cols) {
			throw std::out_of_range("Ha!");
		} else {
			Matrix nmatr(rows, cols);
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					nmatr[i][j] = arr[i][j] + matr[i][j];
				}
			}
			return nmatr;
		}
	}

	bool operator==(const Matrix &matr) {
		if ((rows != matr.rows) || (cols != matr.cols)) {
			return false;
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (arr[i][j] != matr[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator!=(const Matrix &matr) {
		if ((rows != matr.rows) || (cols != matr.cols)) {
			return true;
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (arr[i][j] != matr[i][j]) {
					return true;
				}
			}
		}
		return false;
	}

	~Matrix() {
		for (int i = 0; i < rows; ++i) {
			delete[] arr[i];
		}
		delete[] arr;
		arr = nullptr;
	}
};

std::ostream& operator<<(std::ostream &out, const Matrix &matr) {
	for (int i = 0; i < matr.rows; ++i) {
		for (int j = 0; j < matr.cols; ++j) {
			out << matr[i][j] << " ";
		}
		out << std::endl;
	}
	return out;
}

void Test1() {
	const size_t rows = 5;
	const size_t cols = 3;

	Matrix m(rows, cols);

	assert(m.getRows() == 5);
	assert(m.getColumns() == 3);

	m[1][2] = 5;
	m[4][1] = 10;
	double x = m[4][1];
	assert(x == 10.0);

	m *= 3;
	std::cout << m; 

	Matrix m1(rows, cols);
	m1[1][2] = 15;
	m1[4][1] = 30;
	if (m1 == m) {
		std::cout << "They're equal!" << std::endl;
	} else {
		std::cout << "Oh, they aren't" << std::endl;
	}
	Matrix m2 = m1 + m;
	std::cout << m2 << std::endl;
	assert(m2[1][2] == 30);
	assert(m2[4][1] == 60);
}

void Test2() {
	Matrix m1(4, 5);
	try {
		m1[5][2] = -1;
	}
	catch (const std::out_of_range &oor) {
		std::cerr << oor.what() << std::endl;
	}
	Matrix m2(4, 7);
	try {
		Matrix m3 = m1 + m2;
	}
	catch (const std::out_of_range &oor) {
		std::cerr << oor.what() << std::endl;
	}
}

int main() {
	Test1();
	Test2();
}