#pragma once
#include "Matrix.h"
#include "Shapes/Shape.h"

class Vector;
class Matrix;
class Shape;

class Camera : public Shape
{
public:
    Camera(World* graph);
    ~Camera();

    Matrix lookatMatrix();

    void drawInWindow(SDL_Renderer& renderer, Vector& vector1, Vector& vector2);

    void setLookAt(Shape* lookAt) { lookAt_ = lookAt; }

    void move() override;
    void moveX(float amount);
    void moveY(float amount);
    void moveZ(float amount);
    void zoom(float amount);

    void rotateHorizontal(double degrees);
    void rotateVertical(double degrees);

private:
    World* graph_;
    Matrix projectionMatrix_;
    Shape* lookAt_;
    double far_;
    double near_;
    double fovy_;
};

