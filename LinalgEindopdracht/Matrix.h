#pragma once
#include <vector>

class Vector;

class Matrix
{
public:
	explicit Matrix(int rows, int cols = 1);

	Matrix operator+(Matrix const& other);
	Matrix operator-(Matrix const& other);
	Matrix operator*(Vector const& vector);
	Matrix operator*(Matrix const& other);

	std::vector<std::vector<double>>* elems();
	void setValue(int x, int y, double value);
private:
	int rows_;
	int cols_;
	std::vector<std::vector<double>> elems_;
};
