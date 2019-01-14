#pragma once
#include "Shape.h"
#include "../Vector.h"

class CollidableShape : public Shape
{
public:
	CollidableShape(std::vector<Vector> vectors, std::vector<std::pair<Vector*, Vector*>> edges, Vector position);
	~CollidableShape();

	virtual bool collidesWith(Shape& shape);


	double& sphereRadius() { return sphereRadius_; }

protected:
	Vector center_;
	double sphereRadius_;
};

