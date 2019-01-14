#include "Vector.h"
#include "Graph.h"


Vector::Vector(double x, double y, double z) : x_(x), y_(y), z_(z)
{

}


Vector::~Vector() {}

void Vector::drawVector(SDL_Renderer& renderer) const
{
    SDL_RenderDrawLine(&renderer, 300, 300, 300 + x_ * 60, 300 + y_ * -60); // Window is 600x600 so multiply by 60
}

void Vector::drawAsPoint(SDL_Renderer& renderer) const
{
    SDL_SetRenderDrawColor(&renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_Rect rect{ pixelX() - 2, pixelY() - 2, 4, 4 };
    SDL_RenderDrawRect(&renderer, &rect);
}

void Vector::multiply(double scale)
{
    x_ = x_ * scale;
    y_ = y_ * scale;
    z_ = z_ * scale;
}

void Vector::add(const Vector& vector)
{
    x_ += vector.x_;
    y_ += vector.y_;
    z_ += vector.z_;
}

void Vector::subtract(Vector& vector)
{
    x_ -= vector.x_;
    y_ -= vector.y_;
    z_ -= vector.z_;
}

double Vector::x() const
{
    return x_;
}

void Vector::setX(double x)
{
    x_ = x;
}

void Vector::setY(double y)
{
    y_ = y;
}

double Vector::y() const
{
    return y_;
}

double Vector::z() const
{
    return z_;
}

void Vector::setZ(double z)
{
    z_ = z;
}


double Vector::pixelX() const
{
    return 300 + x_ * 60;
}

double Vector::pixelY() const
{
    return 300 + y_ * -60;
}

double Vector::pixelZ() const
{
    return 300 + z_ * -60;
}


double Vector::dotProduct(Vector& w) const
{
    return x_ * w.x() + y_ * w.y() + z_ * w.z();
}

Vector Vector::crossProduct(Vector& w) const
{
    Vector result{ 0, 0, 0 };

    result.setX(y_ * w.z() - z_ * w.y());
    result.setY(z_ * w.x() - x_ * w.z());
    result.setZ(x_ * w.y() - y_ * w.x());

    return result;
}

double Vector::length() const
{
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

void Vector::normalize()
{
    const double vLength = length();

    x_ /= vLength;
    y_ /= vLength;
    z_ /= vLength;
}
