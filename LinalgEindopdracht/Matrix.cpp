#include "Matrix.h"
#include "Vector.h"


Matrix::Matrix(int rows, int cols) : rows_{ rows }, cols_{ cols }
{
	elems_ = std::vector<std::vector<double>>{};
	elems_.resize(rows);

	for (int y = 0; y < rows; y++)
	{
		elems_[y] = std::vector<double>{};
		elems_[y].resize(cols);
	}
}

Matrix Matrix::operator+(Matrix const& other)
{
	Matrix result(rows_, cols_);

	for (int y = 0; y < rows_; ++y)
		for (int x = 0; x < cols_; ++x)
			result.elems_[y][x] = elems_[y][x] + other.elems_[y][x];

	return result;
}

Matrix Matrix::operator-(Matrix const& other)
{
	Matrix result(rows_, cols_);

	for (int y = 0; y < rows_; ++y)
		for (int x = 0; x < cols_; ++x)
			result.elems_[y][x] = elems_[y][x] - other.elems_[y][x];

	return result;
}

Matrix Matrix::operator*(Vector const& vector)
{
	Matrix result(rows_, 1);

	if (cols_ != 2)
		return result;

	for (int y = 0; y < rows_; y++)
	{
		result.elems_[y][0] = elems_[y][0] * vector.x() + elems_[y][1] * vector.y() + elems_[y][2] * vector.z();
	}

	return result;
}

Matrix Matrix::operator*(Matrix const& other)
{
	Matrix result(rows_, other.cols_);

	if (cols_ != other.rows_)
		return result;

	for (int i = 0; i < rows_; ++i)
	{
		for (int j = 0; j < other.cols_; ++j)
		{
			for (int k = 0; k < cols_; ++k)
			{
				result.elems_[i][j] += elems_[i][k] * other.elems_[k][j];
			}
		}
	}

	return result;
}

std::vector<std::vector<double>>* Matrix::elems()
{
	return &elems_;
}

void Matrix::setValue(int x, int y, double value)
{
	elems_[x][y] = value;
}