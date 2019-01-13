#include "SpaceShip.h"
#include "Camera.h"


SpaceShip::SpaceShip(std::vector<Vector> vectors, std::vector<std::pair<Vector*, Vector*>> edges, Vector position) : Shape(std::move(vectors), std::move(edges), std::move(position))
{
}


SpaceShip::~SpaceShip()
{
}

void SpaceShip::turnHorizontal(float degrees)
{
    // Vector start{ position_ };
    // Vector end{ position_.x(), position_.y() + 0.5, position_.z() };

    rotateAroundRandomAxis(degrees, position_, vectors_[3]);
}

void SpaceShip::turnVertical(float degrees)
{
    rotateAroundRandomAxis(degrees, position_, vectors_[1]);
}

void SpaceShip::roll(float degrees)
{
    rotateAroundRandomAxis(degrees, position_, vectors_[2]);
}

void SpaceShip::fly()
{
    Vector direction{ vectors_[2] };

    Vector middlePosition{ position_ };
    direction.subtract(middlePosition);

    direction.normalize();
    //direction.multiply(0.1);

    position_.add(direction);

    //updateVectors();

    for (auto& vector : vectors_)
    {
	vector.add(direction);
    }
}

void SpaceShip::render(SDL_Renderer& renderer, Camera& camera)
{
    camera.drawInWindow(renderer, position_, vectors_[3]);
    camera.drawInWindow(renderer, position_, vectors_[1]);
    camera.drawInWindow(renderer, position_, vectors_[2]);

    Shape::render(renderer, camera);
}
