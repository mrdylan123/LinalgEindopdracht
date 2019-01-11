#pragma once
#include "Vector.h"
#include "Matrix.h"

class Camera
{
public:
	Camera(Graph* graph);
	~Camera();

	Matrix lookatMatrix();

	Vector getWindowLocation(Vector& vector);

	Vector& position() { return position_; }

private:
	Graph* graph_;
	Matrix projectionMatrix_;
	Vector position_;
	double far_;
	double near_; // Anything below this value doesn't have to be drawn
	double fovy_;
};

