#include "Graph.h"
#include "Matrix.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector.h"

Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::draw(SDL_Renderer& renderer)
{
	SDL_SetRenderDrawColor(&renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(&renderer, 0, 300, 600, 300); // X-axis
	SDL_RenderDrawLine(&renderer, 300, 0, 300, 600); // Y-axis

	// Get all vectors and draw them aswell
	for (Vector* vector : vectors)
	{
		//vector->drawAsPoint(renderer);
	}
}

void Graph::addVector(Vector* vector)
{
	vectors.emplace_back(vector);
}

void Graph::drawShape(SDL_Renderer& renderer, std::vector<std::pair<Vector, Vector>>& edges, View view) const
{

	for (std::pair<Vector, Vector>& edge : edges)
	{
		int x1, x2, y1, y2;

		switch (view)
		{
		case Top:
			x1 = edge.first.pixelX();
			x2 = edge.second.pixelX();
			y1 = edge.first.pixelZ();
			y2 = edge.second.pixelZ();
			break;
		case Front:
			x1 = edge.first.pixelX();
			x2 = edge.second.pixelX();
			y1 = edge.first.pixelY();
			y2 = edge.second.pixelY();
			break;
		case Side:
			x1 = edge.first.pixelZ();
			x2 = edge.second.pixelZ();
			y1 = edge.first.pixelY();
			y2 = edge.second.pixelY();
			break;
		}

		SDL_RenderDrawLine(&renderer, x1, y1, x2, y2);
	}
}

void Graph::scale(int factorX, int factorY, int factorZ)
{
	Matrix scalingMatrix = Matrix{ 4, 4 };

	scalingMatrix.setValue(0, 0, factorX);
	scalingMatrix.setValue(1, 1, factorY);
	scalingMatrix.setValue(2, 2, factorZ);
	scalingMatrix.setValue(3, 3, 1);

	for (auto& vector : vectors)
	{
		Matrix result = scalingMatrix * *vector;
		vector->setX((*result.elems())[0][0]);
		vector->setY((*result.elems())[1][0]);
		vector->setZ((*result.elems())[2][0]);
	}
}

void Graph::scaleFromPoint(int factorX, int factorY, int factorZ, Vector& point)
{
	translate(-point.x(), -point.y(), -point.z());
	scale(factorX, factorY, factorZ);
	translate(point.x(), point.y(), point.z());
}

void Graph::translate(int xDirection, int yDirection, int zDirection)
{
	Matrix translationMatrix = Matrix{ 4, 4 };

	translationMatrix.setValue(0, 0, 1);
	translationMatrix.setValue(1, 1, 1);
	translationMatrix.setValue(2, 2, 1);
	translationMatrix.setValue(3, 3, 1);
	translationMatrix.setValue(2, 0, xDirection);
	translationMatrix.setValue(2, 1, yDirection);
	translationMatrix.setValue(2, 2, zDirection);

	for (auto& vector : vectors)
	{
		Matrix vectorMatrix = Matrix{ 1, 4 };
		vectorMatrix.setValue(0, 0, vector->x());
		vectorMatrix.setValue(0, 1, vector->y());
		vectorMatrix.setValue(0, 2, vector->z());
		vectorMatrix.setValue(0, 3, 1);

		Matrix result = vectorMatrix * translationMatrix;
		vector->setX((*result.elems())[0][0]);
		vector->setY((*result.elems())[0][1]);
		vector->setZ((*result.elems())[0][2]);
	}
}

void Graph::rotate(int degrees)
{
	Matrix rotationMatrix = Matrix{ 2, 2 };

	const double radians = static_cast<double>(degrees) / 180.0 * static_cast<double>(M_PI);

	rotationMatrix.setValue(0, 0, cos(radians));
	rotationMatrix.setValue(0, 1, -sin(radians));
	rotationMatrix.setValue(1, 0, sin(radians));
	rotationMatrix.setValue(1, 1, cos(radians));

	for (auto& vector : vectors)
	{
		Matrix result = rotationMatrix * *vector;
		vector->setX((*result.elems())[0][0]);
		vector->setY((*result.elems())[1][0]);
	}
}

void Graph::rotateFromPoint(int degrees, Vector& point)
{
	translate(-point.x(), -point.y(), -point.z());
	rotate(degrees);
	translate(point.x(), point.y(), point.z());
}