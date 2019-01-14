#include "Camera.h"
#include "Matrix.h"
#include "Graph.h"
#include "Shape.h"
#include "Vector.h"
#include <corecrt_math_defines.h>


Camera::Camera(Graph* graph) : Shape(std::vector<Vector>{{0, 1.5, 1}}, std::vector<std::pair<Vector*, Vector*>>{}, { 0, 1.5, 1 }), graph_{ graph }, projectionMatrix_{ 4, 4 }, fovy_{ 90 }, near_{ 0.1 }, far_{ 100 }
{
	double povyRad = fovy_ / 180.0 * static_cast<double>(M_PI);
	double scale = near_ * tan(povyRad * 0.5);

	projectionMatrix_.setValue(0, 0, scale);
	projectionMatrix_.setValue(1, 1, scale);
	projectionMatrix_.setValue(2, 2, -far_ / (far_ - near_));
	projectionMatrix_.setValue(2, 3, -far_ * near_ / (far_ - near_));
	projectionMatrix_.setValue(3, 2, -1);

	position_ = vectors_[0];
}


Camera::~Camera()
{
}

Matrix Camera::lookatMatrix()
{
	Vector lookat{ lookAt_->position().x(), lookAt_->position().y(), lookAt_->position().z() };
	//Vector lookat{ 0,1,0 };
	Vector eye_{ position_.x(), position_.y(), position_.z() };
	eye_.subtract(lookat);

	Vector direction = eye_;
	direction.normalize();

	Vector up{ 0, 1, 0 };

	Vector right = up.crossProduct(direction);
	right.normalize();

	up = direction.crossProduct(right);

	up.normalize();

	Matrix m{ 4, 4 };
	m.setValue(0, 0, right.x());
	m.setValue(0, 1, up.x());
	m.setValue(0, 2, direction.x());
	m.setValue(1, 0, right.y());
	m.setValue(1, 1, up.y());
	m.setValue(1, 2, direction.y());
	m.setValue(2, 0, right.z());
	m.setValue(2, 1, up.z());
	m.setValue(2, 2, direction.z());
	m.setValue(3, 0, -right.dotProduct(position_));
	m.setValue(3, 1, -up.dotProduct(position_));
	m.setValue(3, 2, -direction.dotProduct(position_));
	m.setValue(3, 3, 1);

	return m;
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
		double x1 = (*projectionResultMatrix1.elems())[0][0] / (*projectionResultMatrix1.elems())[3][0];
		double y1 = (*projectionResultMatrix1.elems())[1][0] / (*projectionResultMatrix1.elems())[3][0];

		double x2 = (*projectionResultMatrix2.elems())[0][0] / (*projectionResultMatrix2.elems())[3][0];
		double y2 = (*projectionResultMatrix2.elems())[1][0] / (*projectionResultMatrix2.elems())[3][0];

		SDL_RenderDrawLine(&renderer, 300 + x1 * 60, 300 + y1 * -60, 300 + x2 * 60, 300 + y2 * -60);
	}
}

void Camera::move()
{
}

void Camera::moveX(float amount)
{
	position_.setX(position_.x() + amount);
	vectors_[0].setX(vectors_[0].x() + amount);
}

void Camera::moveY(float amount)
{
	position_.setY(position_.y() + amount);
	vectors_[0].setY(vectors_[0].y() + amount);
}

void Camera::rotateHorizontal(double degrees)
{
	Vector startPoint{ lookAt_->position() };

	const Vector endPoint{ startPoint.x(), startPoint.y() + 1, startPoint.z() };

	rotateAroundRandomAxis(degrees, startPoint, endPoint);

	position_ = vectors_[0];
}

void Camera::rotateVertical(double degrees)
{
	Vector startPoint{ lookAt_->position() };

	const Vector endPoint{ startPoint.x() + 1, startPoint.y(), startPoint.z()};

	rotateAroundRandomAxis(degrees, startPoint, endPoint);

	position_ = vectors_[0];
}