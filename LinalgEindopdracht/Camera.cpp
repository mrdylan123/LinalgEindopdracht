#include "Camera.h"
#include "Matrix.h"
#include "Graph.h"
#include "Shape.h"
#include <iostream>
#include <string>
#include <corecrt_math_defines.h>


Camera::Camera(Graph* graph) : graph_{ graph }, projectionMatrix_{ 4, 4 }, position_{ 0, 2, 1 }, fovy_{ 90 }, near_{ 0.1 }, far_{ 100 }
{
    double povyRad = fovy_ / 180.0 * static_cast<double>(M_PI);
    double scale = near_ * tan(povyRad * 0.5);

    projectionMatrix_.setValue(0, 0, scale);
    projectionMatrix_.setValue(1, 1, scale);
    projectionMatrix_.setValue(2, 2, -far_ / (far_ - near_));
    projectionMatrix_.setValue(2, 3, -far_ * near_ / (far_ - near_));
    projectionMatrix_.setValue(3, 2, -1);
}


Camera::~Camera()
{
}

Matrix Camera::lookatMatrix()
{
    //ector lookat{ lookAt_->position().x(), lookAt_->position().y(), lookAt_->position().z() };
    Vector lookat{ 0,0,0 };
    Vector eye_{ position_.x(), position_.y(), position_.z() };
    eye_.subtract(lookat);

    Vector direction = eye_;
    direction.normalize();

    Vector up{ 0, 1, 0 };

    Vector right = up.crossProduct(direction);
    right.normalize();

    up = direction.crossProduct(right);

    up.normalize();

    //z = direction
    //x = right
    //y = up

    Matrix m{ 4, 4 };
    m.setValue(0, 0, right.x()); // right.x
    m.setValue(0, 1, up.x()); // up.x
    m.setValue(0, 2, direction.x()); // direction.x
    m.setValue(1, 0, right.y()); // right.y
    m.setValue(1, 1, up.y()); // up.y
    m.setValue(1, 2, direction.y()); // direction.y
    m.setValue(2, 0, right.z()); // right.z
    m.setValue(2, 1, up.z()); // up.z
    m.setValue(2, 2, direction.z()); // direction.z
    m.setValue(3, 0, -right.dotProduct(position_));
    m.setValue(3, 1, -up.dotProduct(position_));
    m.setValue(3, 2, -direction.dotProduct(position_));
    m.setValue(3, 3, 1);

    return m;

    //Matrix m2{ 4, 4 };
    //m2.setValue(3, 0, -position_.x());
    //m2.setValue(3, 1, -position_.y());
    //m2.setValue(3, 2, -position_.z());
    //m2.setValue(0, 0, 1);
    //m2.setValue(1, 1, 1);
    //m2.setValue(2, 2, 1);
    //m2.setValue(3, 3, 1);

    //Matrix resultMatrix = m * m2;

    for (auto& shape : *graph_->getShapes())
    {
	for (auto& vector : shape->vectors())
	{
	    Matrix vMatrix{ 4, 1 };
	    vMatrix.setValue(0, 0, vector.x());
	    vMatrix.setValue(0, 1, vector.y());
	    vMatrix.setValue(0, 2, vector.z());
	    vMatrix.setValue(0, 3, 1);

	    Matrix m3 = m * vMatrix;

	    vector.setX((*m3.elems())[0][0]);
	    vector.setY((*m3.elems())[1][0]);
	    vector.setZ((*m3.elems())[2][0]);
	}
    }
}

void Camera::drawInWindow(SDL_Renderer& renderer, Vector& vector1, Vector& vector2)
{
    Matrix v1Matrix{ 4, 1 };
    v1Matrix.setValue(0, 0, vector1.x());
    v1Matrix.setValue(0, 1, vector1.y());
    v1Matrix.setValue(0, 2, vector1.z());
    v1Matrix.setValue(0, 3, 1);

    Matrix v2Matrix{ 4, 1 };
    v2Matrix.setValue(0, 0, vector2.x());
    v2Matrix.setValue(0, 1, vector2.y());
    v2Matrix.setValue(0, 2, vector2.z());
    v2Matrix.setValue(0, 3, 1);

    Matrix lookatMatrix1 = lookatMatrix() * v1Matrix;
    Matrix lookatMatrix2 = lookatMatrix() * v2Matrix;

    Matrix projectionResultMatrix1 = projectionMatrix_ * lookatMatrix1;
    Matrix projectionResultMatrix2 = projectionMatrix_ * lookatMatrix2;

    if ((*projectionResultMatrix1.elems())[3][0] > 0 && (*projectionResultMatrix2.elems())[3][0] > 0)
    {
	double x1 = (*lookatMatrix1.elems())[0][0] / (*lookatMatrix1.elems())[3][0];
	double y1 = (*lookatMatrix1.elems())[1][0] / (*lookatMatrix1.elems())[3][0];

	double x2 = (*lookatMatrix2.elems())[0][0] / (*lookatMatrix2.elems())[3][0];
	double y2 = (*lookatMatrix2.elems())[1][0]/ (*lookatMatrix2.elems())[3][0];

	SDL_RenderDrawLine(&renderer, 300 + x1 * 60, 300 + y1 * -60, 300 + x2 * 60, 300 + y2 * -60);
    }
}

void Camera::moveX(float amount)
{
    position_.setX(position_.x() + amount);
}

void Camera::moveY(float amount)
{
    position_.setY(position_.y() + amount);
}