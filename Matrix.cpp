#include "Matrix.h"
#include <iomanip>

Matrix::MatrixData::MatrixData(int rows, int cols)
{
	try {
		if (rows <= 0 || cols <= 0) {
			throw InvalidDimensionsException(
				"Matrix dimensions must be positive");
		}
		this->rows = rows;
		this->cols = cols;
		this->referenceCount = 1;
		this->data = new double[this->rows * this->cols]();
	}
	catch (const std::bad_alloc& e) {
		if (this->data != nullptr) {
			delete[] this->data;
			this->data = nullptr;
		}
		cerr << "bad_alloc caught: " << e.what() << '\n';
	}
}
Matrix::MatrixData::MatrixData(const MatrixData& other)
	: data(new double[other.rows * other.cols]), rows(other.rows),
	  cols(other.cols), referenceCount(1)
{
	std::copy(other.data, other.data + (other.rows * other.cols), data);
}
void Matrix::MatrixData::increasereferenceCount()
{

		++referenceCount;

}
void Matrix::MatrixData::decreasereferenceCount()
{
	if (referenceCount > 0) {
		--referenceCount;
	}
}
Matrix::MatrixData::~MatrixData()
{
	decreasereferenceCount();
	if (referenceCount == 0) {
		delete[] data;
	}
}
Matrix::MatrixData* Matrix::MatrixData::detach()
{
	if (referenceCount == 1) {
		return this;
	}
	MatrixData* newcopy = new MatrixData(*this);
	decreasereferenceCount();
	return newcopy;
}
// constructor
Matrix::Matrix() : matrixData(nullptr) {}
Matrix::Matrix(int rows, int cols)
{
	matrixData = new MatrixData(rows, cols);
}
Matrix::Matrix(const Matrix& other)
{
	if (other.matrixData) {
		matrixData = other.matrixData;
		matrixData->increasereferenceCount();
	}
	else {
		matrixData = nullptr;
	}
}
Matrix::~Matrix()
{
	releaseMatrixData();
}
void Matrix::releaseMatrixData()
{

	matrixData->decreasereferenceCount();
	if (matrixData->referenceCount == 0) {
		delete matrixData;
		matrixData = nullptr;
	}
}
int Matrix::getRow() const
{
	try {
		if (this->matrixData != nullptr) {
			return matrixData->rows;
		}
		else {
			throw NullMatrixDataException("null matrix");
		}
	}
	catch (const NullMatrixDataException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}
int Matrix::getCol() const
{
	try {
		if (this->matrixData != nullptr) {
			return matrixData->cols;
		}
		else {
			throw NullMatrixDataException("null matrix");
		}
	}
	catch (const NullMatrixDataException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}

const double Matrix::operator()(int i, int j) const
{
	try {
		if (matrixData) {
			if (i < 0 || i >= matrixData->rows || j < 0 ||
				j >= matrixData->cols) {
				throw MatrixIndexOutOfRangeException("Index is out of range");
			}
			else {
				return matrixData->data[i * matrixData->cols + j];
			}
		}
		else {
			throw NullMatrixDataException("Null matrix");
		}
	}
	catch (const NullMatrixDataException& e) {
		cerr << e.what() << endl;
		throw e;
	}
	catch (const MatrixIndexOutOfRangeException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}

Matrix::Matref Matrix::operator()(int i, int j)
{
	try {
		if (matrixData) {
			matrixData = matrixData->detach();
			if (i < 0 || i >= matrixData->rows || j < 0 ||
				j >= matrixData->cols) {
				throw MatrixIndexOutOfRangeException("Index is out of range");
			}
			else {
				 return Matref(*this, i ,j);
			}
		}
		else {
			throw NullMatrixDataException("Null matrix");
		}
	}
	catch (const NullMatrixDataException& e) {
		cerr << e.what() << endl;
		throw e;
	}
	catch (const MatrixIndexOutOfRangeException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}

///////////////////////////////////////operators//////////////////////////////////////////////
ostream& operator<<(ostream& os, const Matrix& matrix)
{
	int row = matrix.getRow();
	int col = matrix.getCol();
	os << "\n";
	for (int b = 0; b < row; b++) {
		for (int h = 0; h < col; h++) {
			cout << setprecision(1) << fixed;
			os << (double)matrix(b, h) << "    ";
		}
		os << "\n\n";
	}
	return os;
}
Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other) {
		other.matrixData->increasereferenceCount();
		matrixData->decreasereferenceCount();
		if (matrixData->referenceCount == 0)
			delete matrixData;
		matrixData = other.matrixData;
	}
	return *this;
}
// arithmetic operations
Matrix& Matrix::operator+=(const Matrix& other)
{
	try {
		if (matrixData && other.matrixData) {
			if (matrixData->rows != other.matrixData->rows ||
				matrixData->cols != other.matrixData->cols) {
				throw NotProperSizes("the matrises are not equal");
			}
			matrixData = matrixData->detach();
			for (int i = 0; i < matrixData->rows; ++i) {
				for (int j = 0; j < matrixData->cols; ++j) {
					(*this)(i, j) = static_cast<double>((*this)(i, j)) + other(i, j);
				}
			}

			return *this;
		}
		else {
			throw NullMatrixDataException("null matrix");
		}
	}
	catch (const NotProperSizes& e) {
		cerr << e.what() << endl;
		throw e;
	}
	catch (const NullMatrixDataException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}
Matrix Matrix::operator+(const Matrix& other) const
{
	try {
		if (matrixData && other.matrixData) {
			if (matrixData->rows != other.matrixData->rows ||
				matrixData->cols != other.matrixData->cols) {
				throw NotProperSizes("the matrises are not equal");
			}
			else {

				return Matrix(*this) += other;
			}
		}
		else {
			throw NullMatrixDataException("null matrix");
		}
	}
	catch (const NotProperSizes& e) {
		cerr << e.what() << endl;
		throw e;
	}
	catch (const NullMatrixDataException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}
Matrix& Matrix::operator-=(const Matrix& other)
{
	try {
		if (matrixData && other.matrixData) {
			if (matrixData->rows != other.matrixData->rows ||
				matrixData->cols != other.matrixData->cols) {
				throw NotProperSizes("the matrises are not equal");
			}
			matrixData = matrixData->detach();
			for (int i = 0; i < matrixData->rows; ++i) {
				for (int j = 0; j < matrixData->cols; ++j) {
					(*this)(i, j) = static_cast<double>((*this)(i, j)) - other(i, j);
				}
			}

			return *this;
		}
		else {
			throw NullMatrixDataException("null matrix");
		}
	}
	catch (const NotProperSizes& e) {
		cerr << e.what() << endl;
		throw e;
	}
	catch (const NullMatrixDataException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}
Matrix Matrix::operator-(const Matrix& other) const
{
	try {
		if (matrixData && other.matrixData) {
			if (matrixData->rows != other.matrixData->rows ||
				matrixData->cols != other.matrixData->cols) {
				throw NotProperSizes("the matrises are not equal");
			}
			else {

				return Matrix(*this) -= other;
			}
		}
		else {
			throw NullMatrixDataException("null matrix");
		}
	}
	catch (const NotProperSizes& e) {
		cerr << e.what() << endl;
		throw e;
	}
	catch (const NullMatrixDataException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}
Matrix& Matrix::operator*=(const Matrix& other)
{
	try {
		if (matrixData && other.matrixData) {
			if (matrixData->cols != other.matrixData->rows) {
				throw NotProperSizes(
					"Matrices are not compatible for multiplication");
			}
			Matrix result(matrixData->rows, other.matrixData->cols);

			for (int i = 0; i < matrixData->rows; ++i) {
				for (int j = 0; j < other.matrixData->cols; ++j) {
					double sum = 0.0;
					for (int k = 0; k < matrixData->cols; ++k) {
						sum += matrixData->data[i * matrixData->cols + k] *
							   other.matrixData
								   ->data[k * other.matrixData->cols + j];
					}
					result(i, j) = sum;
				}
			}

			*this = result;

			return *this;
		}
		else {
			throw NullMatrixDataException("Null matrix");
		}
	}
	catch (const NotProperSizes& e) {
		cerr << e.what() << endl;
		throw e;
	}
	catch (const NullMatrixDataException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}
Matrix Matrix::operator*(const Matrix& other) const
{
	try {
		if (this->matrixData && other.matrixData) {
			if (this->matrixData->cols != other.matrixData->rows) {
				throw NotProperSizes(
					"the columns does'nt equal the rows of the other");
			}

			return Matrix(*this) *= other;
		}
		else {
			throw NullMatrixDataException("null matrix");
		}
	}
	catch (const NotProperSizes& e) {
		cerr << e.what() << endl;
		throw e;
	}
	catch (const NullMatrixDataException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}
bool Matrix::operator==(const Matrix& other) const
{
	return arematrisesequal(*this, other);
}
bool Matrix::operator!=(const Matrix& other) const
{
	return !arematrisesequal(*this, other);
}
bool arematrisesequal(const Matrix& A, const Matrix& B)
{
	try {
		if (A.matrixData && B.matrixData) {
			if (A.getRow() != B.getRow() || A.getCol() != B.getCol()) {
				return false;
			}
			for (int i = 0; i < A.getRow(); ++i) {
				for (int j = 0; j < A.getCol(); ++j) {
					if (A(i, j) != B(i, j)) {
						return false;
					}
				}
			}
			return true;
		}
		else {
			throw NullMatrixDataException("null matrix");
		}
	}
	catch (const NullMatrixDataException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}

void Matrix::readFromFile(const string& filename)
{
	try {
		ifstream InputFile(filename);
		if (!InputFile.is_open()) {
			throw FileOpenException("Unable to open file: " + filename);
		}
		this->releaseMatrixData();
		int rows, cols;
		InputFile >> rows >> cols;
		if (rows <= 0 || cols <= 0) {
			throw InvalidDimensionsException(
				"Matrix dimensions must be positive");
		}

		this->matrixData = new MatrixData(rows, cols);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				double value;
                InputFile >> value;
                this->write(i, j, value);
			}
		}
	}
	catch (const FileOpenException& e) {
		cerr << e.what() << endl;
		throw e;
	}
}
double Matrix::read(int row, int col) const
{
	return matrixData->data[row * matrixData->cols + col];
}
void Matrix::write(int row, int col, double value)
{
	matrixData->detach();
	matrixData->data[row * matrixData->cols + col] = value;
}
