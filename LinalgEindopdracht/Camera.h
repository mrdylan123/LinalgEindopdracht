#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Shape.h"

class Camera
{
public:
    Camera(Graph* graph);
    ~Camera();

    Matrix lookatMatrix();

    void drawInWindow(SDL_Renderer& renderer, Vector& vector1, Vector& vector2);

    Vector& position() { return position_; }

    void setLookAt(Shape* lookAt) { lookAt_ = lookAt; }

    void moveX(float amount);
    void moveY(float amount);

private:
    Graph* graph_;
    Matrix projectionMatrix_;
    Vector position_;
    Shape* lookAt_;
    double far_;
    double near_; // Anything below this value doesn't have to be drawn
    double fovy_;
};

