#include "Shape.h"
#include "Matrix.h"
#include <corecrt_math_defines.h>
#include "Camera.h"


Shape::Shape(std::vector<Vector> vectors, std::vector<std::pair<Vector*, Vector*>> edges, Vector position) : vectors_{ std::move(vectors) }, edges_{ std::move(edges) }, position_{ std::move(position) }, speedVector_{ 0, 0, 0 }, speed_{ 0 }
{
	//updateVectors();
}

Shape::~Shape() = default;

void Shape::update(SDL_Renderer& renderer, Camera& camera)
{
	move();

	for (const std::pair<Vector*, Vector*>& edge : edges_)
	{
		camera.drawInWindow(renderer, *edge.first, *edge.second);
	}
}

void Shape::scale(double factorX, double factorY, double factorZ)
{
	Matrix scalingMatrix = Matrix{ 4, 4 };

	scalingMatrix.setValue(0, 0, factorX);
	scalingMatrix.setValue(1, 1, factorY);
	scalingMatrix.setValue(2, 2, factorZ);
	scalingMatrix.setValue(3, 3, 1);

	for (auto& vector : vectors_)
	{
		Matrix vectorMatrix = Matrix{ 4, 1 };
		vectorMatrix.setValue(0, 0, vector.x());
		vectorMatrix.setValue(0, 1, vector.y());
		vectorMatrix.setValue(0, 2, vector.z());
		vectorMatrix.setValue(0, 3, 1);

		Matrix result = scalingMatrix * vectorMatrix;
		vector.setX((*result.elems())[0][0]);
		vector.setY((*result.elems())[1][0]);
		vector.setZ((*result.elems())[2][0]);
	}
}

void Shape::translate(double xDirection, double yDirection, double zDirection)
{
	Matrix translationMatrix = Matrix{ 4, 4 };

	translationMatrix.setValue(0, 0, 1);
	translationMatrix.setValue(1, 1, 1);
	translationMatrix.setValue(2, 2, 1);
	translationMatrix.setValue(3, 3, 1);
	translationMatrix.setValue(3, 0, xDirection);
	translationMatrix.setValue(3, 1, yDirection);
	translationMatrix.setValue(3, 2, zDirection);

	for (auto& vector : vectors_)
	{
		Matrix vectorMatrix = Matrix{ 4, 1 };
		vectorMatrix.setValue(0, 0, vector.x());
		vectorMatrix.setValue(0, 1, vector.y());
		vectorMatrix.setValue(0, 2, vector.z());
		vectorMatrix.setValue(0, 3, 1);

		Matrix result = translationMatrix * vectorMatrix;
		vector.setX((*result.elems())[0][0]);
		vector.setY((*result.elems())[1][0]);
		vector.setZ((*result.elems())[2][0]);
	}
}

void Shape::rotate(double degrees)
{
	Matrix rotationMatrix = Matrix{ 2, 2 };

	const double radians = static_cast<double>(degrees) / 180.0 * static_cast<double>(M_PI);

	rotationMatrix.setValue(0, 0, cos(radians));
	rotationMatrix.setValue(1, 0, -sin(radians));
	rotationMatrix.setValue(0, 1, sin(radians));
	rotationMatrix.setValue(1, 1, cos(radians));

	for (auto& vector : vectors_)
	{
		Matrix result = rotationMatrix * vector;
		vector.setX((*result.elems())[0][0]);
		vector.setY((*result.elems())[1][0]);
	}
}

void Shape::scaleFromPoint(double factorX, double factorY, double factorZ, Vector point)
{
	translate(-point.x(), -point.y(), -point.z());
	scale(factorX, factorY, factorZ);
	translate(point.x(), point.y(), point.z());
}

void Shape::rotateFromPoint(double degrees, Vector& point)
{
	translate(-point.x(), -point.y(), -point.z());
	rotate(degrees);
	translate(point.x(), point.y(), point.z());
}

void Shape::rotateX(double degrees)
{
	Matrix rotationMatrix = Matrix{ 4, 4 };

	const double radians = static_cast<double>(degrees) / 180.0 * static_cast<double>(M_PI);

	rotationMatrix.setValue(0, 0, 1);
	rotationMatrix.setValue(1, 1, cos(radians));
	rotationMatrix.setValue(1, 2, sin(radians));
	rotationMatrix.setValue(2, 1, -sin(radians));
	rotationMatrix.setValue(2, 2, cos(radians));
	rotationMatrix.setValue(3, 3, 1);

	for (auto& vector : vectors_)
	{
		Matrix vectorMatrix = Matrix{ 4, 1 };
		vectorMatrix.setValue(0, 0, vector.x());
		vectorMatrix.setValue(0, 1, vector.y());
		vectorMatrix.setValue(0, 2, vector.z());
		vectorMatrix.setValue(0, 3, 1);

		Matrix result = rotationMatrix * vectorMatrix;
		vector.setX((*result.elems())[0][0]);
		vector.setY((*result.elems())[1][0]);
		vector.setZ((*result.elems())[2][0]);
	}
}

void Shape::rotateY(double degrees)
{
	Matrix rotationMatrix = Matrix{ 4, 4 };

	const double radians = static_cast<double>(degrees) / 180.0 * static_cast<double>(M_PI);

	rotationMatrix.setValue(0, 0, cos(radians));
	rotationMatrix.setValue(0, 2, -sin(radians));
	rotationMatrix.setValue(1, 1, 1);
	rotationMatrix.setValue(2, 0, sin(radians));
	rotationMatrix.setValue(2, 2, cos(radians));
	rotationMatrix.setValue(3, 3, 1);

	for (auto& vector : vectors_)
	{
		Matrix vectorMatrix = Matrix{ 4, 1 };
		vectorMatrix.setValue(0, 0, vector.x());
		vectorMatrix.setValue(0, 1, vector.y());
		vectorMatrix.setValue(0, 2, vector.z());
		vectorMatrix.setValue(0, 3, 1);

		Matrix result = rotationMatrix * vectorMatrix;
		vector.setX((*result.elems())[0][0]);
		vector.setY((*result.elems())[1][0]);
		vector.setZ((*result.elems())[2][0]);
	}
}

void Shape::rotateZ(double degrees)
{
	Matrix rotationMatrix = Matrix{ 4, 4 };

	const double radians = static_cast<double>(degrees) / 180.0 * static_cast<double>(M_PI);

	rotationMatrix.setValue(0, 0, cos(radians));
	rotationMatrix.setValue(0, 1, sin(radians));
	rotationMatrix.setValue(1, 0, -sin(radians));
	rotationMatrix.setValue(1, 1, cos(radians));
	rotationMatrix.setValue(2, 2, 1);
	rotationMatrix.setValue(3, 3, 1);

	for (auto& vector : vectors_)
	{
		Matrix vectorMatrix = Matrix{ 4, 1 };
		vectorMatrix.setValue(0, 0, vector.x());
		vectorMatrix.setValue(0, 1, vector.y());
		vectorMatrix.setValue(0, 2, vector.z());
		vectorMatrix.setValue(0, 3, 1);

		Matrix result = rotationMatrix * vectorMatrix;
		vector.setX((*result.elems())[0][0]);
		vector.setY((*result.elems())[1][0]);
		vector.setZ((*result.elems())[2][0]);
	}
}

void Shape::updateVectors()
{
	for (auto& vector : vectors_)
	{
		vector.add(position_);
	}
}

void Shape::rotateAroundAxis(double degrees, Vector& axis)
{
	const float tau = axis.x() != 0 ? atan(axis.z() / axis.x()) : 0;
	const float taudegrees = tau / static_cast<double>(M_PI) * 180;

	rotateY(taudegrees);

	const float cosTau2 = sqrt(pow(axis.x(), 2) + pow(axis.z(), 2)) / sqrt(pow(axis.x(), 2) + pow(axis.y(), 2) + pow(axis.z(), 2));
	const float sinTau2 = axis.y() / sqrt(pow(axis.x(), 2) + pow(axis.y(), 2) + pow(axis.z(), 2));

	const float tau2 = acos(cosTau2);
	const float tau2degrees = tau2 / static_cast<double>(M_PI) * 180;

	rotateZ(-tau2degrees);
	rotateX(degrees);
	rotateZ(tau2degrees);
	rotateY(-taudegrees);
}

void Shape::rotateAroundRandomAxis(double degrees, Vector startPoint, Vector endPoint)
{
	endPoint.setX(endPoint.x() - startPoint.x());
	endPoint.setY(endPoint.y() - startPoint.y());
	endPoint.setZ(endPoint.z() - startPoint.z());

	translate(-startPoint.x(), -startPoint.y(), -startPoint.z());
	rotateAroundAxis(degrees, endPoint);


	translate(startPoint.x(), startPoint.y(), startPoint.z());
}