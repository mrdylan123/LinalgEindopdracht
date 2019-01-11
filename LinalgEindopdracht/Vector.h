#pragma once
#include <SDL2/SDL.h>

class Graph;

class Vector
{
public:
	Vector(double x, double y, double z);
	~Vector();

	void drawVector(SDL_Renderer& renderer) const;
	void drawAsPoint(SDL_Renderer& renderer) const;

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
	double z() const;
	void setZ(double z);
	double dotProduct(Vector& w) const;
	Vector crossProduct(Vector& w) const;
	double length() const;

	void normalize();

private:
	double x_;
	double y_;
	double z_;
};
