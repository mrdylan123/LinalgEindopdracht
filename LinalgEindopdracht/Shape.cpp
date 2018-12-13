#include "Shape.h"


Shape::Shape(std::vector<Vector> vectors, std::vector<std::pair<Vector, Vector>> edges) : vectors_{ std::move(vectors) }, edges_{ std::move(edges) }
{
}

Shape::~Shape() = default;
