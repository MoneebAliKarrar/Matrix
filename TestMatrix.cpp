#include "Matrix.h"
#include <iostream>
using namespace std;
void display(const Matrix& a, const Matrix& b);
void test(const Matrix& A, const Matrix& B);
void testAddition(const Matrix& A, const Matrix& B);
void testSubtraction(const Matrix& A, const Matrix& B);
void testMultiplication(const Matrix& A, const Matrix& B);
void testAdditionAssignment(const Matrix& A, const Matrix& B);
void testSubtractionAssignment(const Matrix& A, const Matrix& B);
void testMultiplicationAssignment(const Matrix& A, const Matrix& B);
void testComparison(const Matrix& A, const Matrix& B);
void singleElementAccess(const Matrix& A);
void testConstructor();
void testAssignment();
void testReadFile();
void testExceptions();
void testNotProperSizes();
void testInvalidDimensionsException();
void testMatrixIndexOutOfRangeException();
void testReferenceCounting();

int main()
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "out and initial Matrix numbers " << endl;
	Matrix A(2, 2);
	Matrix B(2, 2);
	for (int i = 0; i < A.getRow(); ++i) {
		for (int j = 0; j < A.getCol(); ++j) {
			A(i, j) = (i / 2.0) + j;
			B(i, j) = i - (j / 2.0);
		}
	}
	display(A, B);
	test(A, B);
}
void test(const Matrix& A, const Matrix& B)
{
	testAddition(A, B);
	testSubtraction(A, B);
	testMultiplication(A, B);
	testAdditionAssignment(A, B);
	testSubtractionAssignment(A, B);
	testMultiplicationAssignment(A, B);
	testComparison(A, B);
	testConstructor();
	testAssignment();
	singleElementAccess(A);
	testReferenceCounting();
	testExceptions();
	testReadFile();
}
void testExceptions()
{
	testNotProperSizes();
	testInvalidDimensionsException();
	testMatrixIndexOutOfRangeException();
}
void display(const Matrix& A, const Matrix& B)
{
	cout << "Matrix A: " << A << endl;
	cout << "Matrix B: " << B << endl;
}
void testConstructor()
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "constructor " << endl;
	Matrix C(3, 3);
	for (int i = 0; i < C.getRow(); ++i) {
		for (int j = 0; j < C.getCol(); ++j) {
			C(i, j) = i / 2.0 + j;
		}
	}
	Matrix D(C);
	cout << D << endl;
}
void testAssignment()
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "assignment " << endl;
	Matrix C(3, 3);
	for (int i = 0; i < C.getRow(); ++i) {
		for (int j = 0; j < C.getCol(); ++j) {
			C(i, j) = i / 2.0 + j;
		}
	}
	Matrix D = C;
	cout << D << endl;
}
void testAddition(const Matrix& A, const Matrix& B)
{

	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "addition " << endl;
	Matrix C = A + B;
	cout << "Sum of Matrixes A and B: " << C << endl;
}
void testSubtraction(const Matrix& A, const Matrix& B)
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "subtracion " << endl;
	cout << "Difference of Matrix A and B: " << A - B << endl;
	cout << "Difference of Matrix B and A: " << B - A << endl;
}
void testMultiplication(const Matrix& A, const Matrix& B)
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "multiplication " << endl;
	cout << "Product of Matrixes A and B: " << A * B << endl;
	cout << "Product of Matrixes B and A: " << B * A << endl;
}

void testAdditionAssignment(const Matrix& A, const Matrix& B)
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "addition and asignment += " << endl;
	Matrix a(2, 2);
	a += A;
	Matrix b(2, 2);
	b = B;
	Matrix c(2, 2);
	Matrix d(2, 2);
	c += a += B;
	(d += a) += B;
	cout << "Addition and assignment of A to Matrix a += A : " << a << endl;
	cout << "Addition and assignment c += a += b : " << c << endl;
	cout << "Addition and assignment (d+=a) += b : " << d << endl;
}

void testSubtractionAssignment(const Matrix& A, const Matrix& B)
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "subtraction and asignment -= " << endl;
	Matrix a(2, 2);
	a -= A;
	Matrix b(2, 2);
	b -= B;
	Matrix c(2, 2);
	Matrix d(2, 2);
	c -= a -= b;
	(d -= a) -= b;
	cout << "subtraction and assignment of A to Matrix a -= A : " << a << endl;
	cout << "subtraction and assignment c -= a -= b : " << c << endl;
	cout << "subtraction and assignment (d-=a) -= b : " << d << endl;
}

void testMultiplicationAssignment(const Matrix& A, const Matrix& B)
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "multiplication and asignment *= " << endl;
	Matrix a(2, 2);
	a = A;
	a *= A;
	Matrix b(2, 2);
	b = B;
	b *= B;
	Matrix c(2, 2);
	c *= a *= b;
	(c *= a) *= b;
	cout << "Multiplication and assignment of A to a : " << a << endl;
	cout << "Multiplication and assignment of     c *= a *= b : " << c << endl;
	cout << "Multiplication and assignment of (c *=a) *= b : " << c << endl;
}
void testComparison(const Matrix& A, const Matrix& B)
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "comparison == and !=" << endl;
	bool s1 = A == A;
	bool s2 = A == B;
	bool s3 = A != A;
	bool s4 = A != B;
	cout << "The value of A == A :" << s1 << endl;
	cout << "The value of A == B :" << s2 << endl;
	cout << "The value of A != A :" << s3 << endl;
	cout << "The value of A != B :" << s4 << endl;
}

void testReadFile()
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "Read from a file test " << endl;
	try {
		Matrix F(3, 3);
		F.readFromFile("MyMatrix.txt");
		cout << "MATRIX F which has been read from file MyMatrix.txt :" << F
			 << endl;
	}
	catch (const InvalidDimensionsException& e) {
		cerr << e.what() << endl;
	}
	catch (const FileOpenException& e) {
		cerr << e.what() << endl;
	}
}
void singleElementAccess(const Matrix& A)
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "single element access" << endl;
	cout << "the first element of the matrix A is :" << A(0, 0) << endl;
}

void testNotProperSizes()
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << " 1 - testNotProperSizes" << endl;
	try {
		Matrix C(3, 2);
		Matrix D(2, 4);
		cout << "the addition of two Matrises which does'nt have the same "
				"dimentions: "
			 << C - D << endl;
	}
	catch (const NotProperSizes& e) {
	}
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << " 2 - testNotProperSizes" << endl;
	try {
		Matrix H(3, 2);
		Matrix J(2, 4);
		cout << "the subtraction of two Matrises which does'nt have the same "
				"dimentions: "
			 << H - J << endl;
	}
	catch (const NotProperSizes& e) {
	}
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << " 3 - testNotProperSizes" << endl;
	try {
		Matrix H(3, 4);
		Matrix J(2, 4);
		cout << "the multiplication of two Matrises which does'nt have the "
				"proper"
				"dimentions: "
			 << H * J << endl;
	}
	catch (const NotProperSizes& e) {
	}
}
void testInvalidDimensionsException()
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "4 - test Invalid Dimensions Exception: " << endl;
	try {

		Matrix H(-1, 0);
	}
	catch (const InvalidDimensionsException& e) {
		cerr << e.what() << endl;
	}
}
void testMatrixIndexOutOfRangeException()
{
	cout << "------------------------------------------------------------------"
			"---"
		 << endl;
	cout << "5 - test Matrix Index Out Of Range Exception" << endl;
	try {
		Matrix A(5, 5);
		A(5, 5) = 7.7;
	}
	catch (const MatrixIndexOutOfRangeException& e) {
	}
}
void testReferenceCounting()
{
	cout
		<< "-------------------------------------------------------------------"
		<< endl;
	cout << "Reference Counting Test" << endl;

	Matrix A(2, 2);

	Matrix B = A;

	Matrix C = B;

	A(0, 0) = 99.9;

	cout << "Matrix B after modifying A: " << B << endl;
	cout << "Matrix C after modifying A: " << C << endl;

	Matrix D = A;

	D(1, 1) = 88.8;

	cout << "Matrix A after modifying D: " << A << endl;
}
