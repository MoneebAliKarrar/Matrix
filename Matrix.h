#pragma once
#include <exception>
#include <fstream>
#include <iostream>
using namespace std;
class Matrix {
  private:
	class MatrixData {
	  public:
		double* data;
		int rows;
		int cols;
		int referenceCount;

		MatrixData(int rows, int cols);
		~MatrixData();

		void increasereferenceCount();
		void decreasereferenceCount();

		MatrixData* detach();

	  private:
		MatrixData(const MatrixData&);
		MatrixData& operator=(const MatrixData&);
	};
	MatrixData* matrixData;
	void releaseMatrixData();

  public:
	class Matref;

	Matrix();
	Matrix(int rows, int cols);
	Matrix(const Matrix& mat);
	~Matrix();

	int getRow() const;
	int getCol() const;

	const double operator()(int i, int j) const; // read only
	Matref operator()(int i, int j);

	Matrix& operator=(const Matrix& other);
	// arithmetic operators
	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	// comparison operators
	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;

	friend bool arematrisesequal(
		const Matrix& A,
		const Matrix& B); // helping matrix compare dimentions of A and B
	void readFromFile(const string& filename);
	friend ostream& operator<<(ostream& os, const Matrix& matrix);

	double read(int row, int col) const;
	void write(int row, int col, double value);
};
class Matrix::Matref {
	friend class Matrix;
	Matrix& matrix;
	int row;
	int col;
	Matref(Matrix& matrixx, int roww, int coll)
		: matrix(matrixx), row(roww), col(coll){};

  public:
	operator double() const
	{
		return matrix.read(row, col);
	}
	Matrix::Matref& operator=(double val)
	{
		matrix.write(row, col, val);
		return *this;
	}
	Matrix::Matref& operator=(const Matref& ref)
	{
		return operator=((double)ref);
	}
};

class InvalidDimensionsException : public std::invalid_argument {
  public:
	InvalidDimensionsException(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};

class MatrixIndexOutOfRangeException : public std::out_of_range {
  public:
	MatrixIndexOutOfRangeException(const std::string& message)
		: std::out_of_range(message)
	{
	}
};

class NullMatrixDataException : public std::runtime_error {
  public:
	NullMatrixDataException(const std::string& message)
		: std::runtime_error(message)
	{
	}
};

class NotProperSizes : public std::runtime_error {
  public:
	NotProperSizes(const std::string& message) : std::runtime_error(message) {}
};

class FileOpenException : public std::runtime_error {
  public:
	FileOpenException(const std::string& message) : std::runtime_error(message)
	{
	}
};
