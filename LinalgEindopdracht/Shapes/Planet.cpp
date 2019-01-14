#include "Planet.h"
#include <xlocinfo.h>
#include <iostream>

Planet::Planet() : CollidableShape(std::vector<Vector> {
	{ 0, 0, 0 },
	{ 1, 0, 0 },
	{ 1, 0, 1 },
	{ 0, 0, 1 },
	{ 0, 1, 0 },
	{ 1, 1, 0 },
	{ 1, 1, 1 },
	{ 0, 1, 1 }}, std::vector<std::pair<Vector*, Vector*>>{}, Vector{ 0, 0, -7 }), sizeRange_{ std::make_pair(1, 5) }, 
	shrinking_{ false }, hits_{ 0 }
{
	center_ = { 0.5, 0.5, 0.5 };
	sphereRadius_ = 0;

	updateVectors();

	// Bottom side
	edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[1]));
	edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[3]));
	edges_.emplace_back(std::make_pair(&vectors_[3], &vectors_[2]));
	edges_.emplace_back(std::make_pair(&vectors_[1], &vectors_[2]));

	// Top side
	edges_.emplace_back(std::make_pair(&vectors_[4], &vectors_[5]));
	edges_.emplace_back(std::make_pair(&vectors_[4], &vectors_[7]));
	edges_.emplace_back(std::make_pair(&vectors_[7], &vectors_[6]));
	edges_.emplace_back(std::make_pair(&vectors_[5], &vectors_[6]));

	// Connect bottom and top side
	edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[4]));
	edges_.emplace_back(std::make_pair(&vectors_[1], &vectors_[5]));
	edges_.emplace_back(std::make_pair(&vectors_[2], &vectors_[6]));
	edges_.emplace_back(std::make_pair(&vectors_[3], &vectors_[7]));
}


	Planet::~Planet()
	{
	}


	void Planet::move()
	{
		Vector size{ vectors_[1] };
		size.subtract(vectors_[0]);

		if (size.x() <= sizeRange_.first) {
			shrinking_ = false;
		}

		if (size.x() >= sizeRange_.second) {
			shrinking_ = true;
		}

		double factor = shrinking_ ? 0.95 : 1.05;

		// Get center of the cube
		Vector upperCorner{ vectors_[6] };
		Vector bottomCorner{ vectors_[0] };
		upperCorner.subtract(bottomCorner);
		upperCorner.multiply(0.5);
		sphereRadius_ = upperCorner.length();
		bottomCorner.add(upperCorner);

		center_ = bottomCorner;

		scaleFromPoint(factor, factor, factor, bottomCorner);
	}

	bool Planet::collidesWith(Shape& shape)
	{
		const bool collision = CollidableShape::collidesWith(shape);

		if (collision)
			hits_++;

		return collision;
	}

void Planet::update(SDL_Renderer& renderer, Camera& camera)
{
	SDL_SetRenderDrawColor(&renderer, 0 + hits_ * 25, 255 - hits_ * 25, 0, SDL_ALPHA_OPAQUE);

	Shape::update(renderer, camera);

	SDL_SetRenderDrawColor(&renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}
