#pragma once
#include <SDL2/SDL.h>
#include "Graph.h"

class Graph;

class Vector
{
public:
	Vector(int x, int y, int z);
	~Vector();

	void drawVector(SDL_Renderer& renderer) const;
	void drawAsPoint(SDL_Renderer& renderer, Graph::View view) const;

	void multiply(int scale);
	void add(Vector& vector);
	void subtract(Vector& vector);

	double x() const;
	void setX(double x);
	double y() const;
	void setY(double y);
	double pixelX() const;
	double pixelY() const;
	double pixelZ() const;

	Vector* next() const;
	void setNext(Vector& next);

private:
	double x_;
	double y_;
	double z_;

public:
	double z() const;
	void setZ(double z);
private:
	Vector* next_;
};
