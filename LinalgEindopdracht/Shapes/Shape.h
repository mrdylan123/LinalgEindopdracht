#pragma once
#include <vector>
#include "../Vector.h"

class Camera;

class Shape
{
public:
	Shape(std::vector<Vector> vectors, std::vector<std::pair<Vector*, Vector*>> edges, Vector position);
	virtual ~Shape();

	virtual void update(SDL_Renderer& renderer, Camera& camera);
	void scale(double factorX, double factorY, double factorZ);
	void scaleFromPoint(double factorX, double factorY, double factorZ, Vector point);
	void translate(double xDirection, double yDirection, double zDirection);
	void rotate(double degrees);
	void rotateFromPoint(double degrees, Vector& point);
	void rotateX(double degrees);
	void rotateY(double degrees);
	void rotateZ(double degrees);

	void updateVectors();
	virtual void move() = 0;

	Vector& position() { return position_; }
	const Vector* speedVector() const { return &speedVector_; }

	void rotateAroundAxis(double degrees, Vector& axis);
	void rotateAroundRandomAxis(double degrees, Vector startPoint, Vector endPoint);

	std::vector<Vector>& vectors() { return vectors_; }
	std::vector<std::pair<Vector*, Vector*>>& edges() { return edges_; }

protected:
	std::vector<Vector> vectors_;
	Vector position_;
	std::vector<std::pair<Vector*, Vector*>> edges_;
	double speed_;
	Vector speedVector_;
	double acceleration_;
};

