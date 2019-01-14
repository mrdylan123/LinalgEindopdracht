#pragma once
#include "Matrix.h"
#include "Shape.h"

class Vector;
class Matrix;
class Shape;

class Camera : public Shape
{
public:
    Camera(Graph* graph);
    ~Camera();

    Matrix lookatMatrix();

    void drawInWindow(SDL_Renderer& renderer, Vector& vector1, Vector& vector2);

    void setLookAt(Shape* lookAt) { lookAt_ = lookAt; }

	void move() override;
    void moveX(float amount);
    void moveY(float amount);

	void rotateHorizontal(double degrees);
	void rotateVertical(double degrees);

private:
    Graph* graph_;
    Matrix projectionMatrix_;
    Shape* lookAt_;
    double far_;
    double near_;
    double fovy_;
};

