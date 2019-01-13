#pragma once
#include <vector>
#include "Vector.h"

class Camera;

class Shape
{
public:
    Shape(std::vector<Vector> vectors, std::vector<std::pair<Vector*, Vector*>> edges, Vector position);
    ~Shape();

    virtual void render(SDL_Renderer& renderer, Camera& camera);
    void scale(int factorX, int factorY, int factorZ);
    void scaleFromPoint(int factorX, int factorY, int factorZ, Vector& point);
    void translate(int xDirection, int yDirection, int zDirection);
    void rotate(int degrees);
    void rotateFromPoint(int degrees, Vector& point);
    void rotateX(float degrees);
    void rotateY(float degrees);
    void rotateZ(float degrees);

    void updateVectors();

    Vector& position() { return position_; }

    void rotateAroundAxis(int degrees, Vector& axis);
    void rotateAroundRandomAxis(int degrees, Vector startPoint, Vector endPoint);

    std::vector<Vector>& vectors() { return vectors_; }
    std::vector<std::pair<Vector*, Vector*>>& edges() { return edges_; }

protected:
    std::vector<Vector> vectors_;
    Vector position_;
    std::vector<std::pair<Vector*, Vector*>> edges_;
};

