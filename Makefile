testMatrix: testMatrix.o Matrix.o
	g++ -g $^ -o $@

Matrix.o: Matrix.cpp Matrix.h
	g++ -g -c -Wall -pedantic $< -o $@

testMatrix.o: testMatrix.cpp Matrix.h
	g++ -g -c -Wall -pedantic $< -o $@

.PHONY: clean

clean:
	-rm Matrix.o testMatrix.o testMatrix