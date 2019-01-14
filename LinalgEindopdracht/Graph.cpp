#include "Graph.h"
#include "Matrix.h"
#define _USE_MATH_DEFINES
#include "Vector.h"
#include "Shape.h"
#include "SpaceShip.h"

Graph::Graph() : camera_{ this }
{
}


Graph::~Graph()
{
}

void Graph::update(SDL_Renderer& renderer)
{
	SDL_SetRenderDrawColor(&renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	if (shapes_.size() > 10)
		shapes_.erase(shapes_.begin() + 1);

	// Get all vectors and draw them aswell
	for (auto& shape : shapes_)
	{
		shape->update(renderer, camera_);
	}

	for (auto& asteroid : asteroids_)
	{
		asteroid->update(renderer, camera_);
	}

	if (planet_ != nullptr)
		planet_->update(renderer, camera_);

	if (planet_ != nullptr && planet_->collidesWith(*shapes_[0]))
	{
		auto spaceship = dynamic_cast<SpaceShip*>(shapes_[0].get());
		spaceship->setDestroyed(true);
	}

	for(auto& asteroid : asteroids_)
	{
		if(asteroid->collidesWith(*shapes_[0]))
		{
			auto spaceship = dynamic_cast<SpaceShip*>(shapes_[0].get());
			spaceship->setDestroyed(true);
		}
	}

	std::vector<std::vector<std::unique_ptr<Shape>>::const_iterator> deleteProjectilesList{};

	// Loop through all projectiles and see if it's near a collision sphere
	for (auto i = shapes_.begin() + 1; i < shapes_.end(); ++i)
	{
		if (planet_ != nullptr && planet_->collidesWith(**i))
		{
			deleteProjectilesList.emplace_back(i);
			if (planet_->hits() >= 10)
				planet_.reset();
		}
	}

	for (auto i = deleteProjectilesList.rbegin(); i < deleteProjectilesList.rend(); ++i)
	{
		shapes_.erase(*i);
	}
}

void Graph::initializeCamera()
{
	camera_.lookatMatrix();
}
