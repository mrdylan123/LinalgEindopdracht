#include "CollidableShape.h"



CollidableShape::CollidableShape(std::vector<Vector> vectors, std::vector<std::pair<Vector*, Vector*>> edges, Vector position) : Shape(vectors, edges, position), center_{0,0,0}, sphereRadius_{0}
{
}


CollidableShape::~CollidableShape()
{
}

bool CollidableShape::collidesWith(Shape& shape)
{
	double distance = 0;

	Vector v{ shape.position() };
	v.subtract(center_);

	distance = sqrt(v.x() * v.x() + v.y() * v.y() + v.z() * v.z());

	return distance < sphereRadius_;
}
