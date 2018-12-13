#pragma once
#include <vector>
#include "Vector.h"
#include <memory>

class Shape
{
public:
    Shape(std::vector<Vector> vectors, std::vector<std::pair<Vector, Vector>> edges);
    ~Shape();

private:
    std::vector<Vector> vectors_;
    std::vector<std::pair<Vector, Vector>> edges_;
};

