#include "Asteroid.h"

Asteroid::Asteroid(const Vector& position) : CollidableShape(std::vector<Vector> {
	{ { 0, 0, 0 }, { 1, 0, 0 }, { 1, 0, 1 }, { 0, 0, 1 }, { 0.5, 1, 0.5} } },
	std::vector<std::pair<Vector*, Vector*>> {}, position)
{
	center_ = { 0.5, 0.5, 0.5 };
	center_.add(position);
	sphereRadius_ = 0.866025;
	updateVectors();
	edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[1]));
	edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[3]));
	edges_.emplace_back(std::make_pair(&vectors_[3], &vectors_[2]));
	edges_.emplace_back(std::make_pair(&vectors_[1], &vectors_[2]));
	edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[4]));
	edges_.emplace_back(std::make_pair(&vectors_[1], &vectors_[4]));
	edges_.emplace_back(std::make_pair(&vectors_[2], &vectors_[4]));
	edges_.emplace_back(std::make_pair(&vectors_[3], &vectors_[4]));
}

Asteroid::~Asteroid()
{
}

void Asteroid::update(SDL_Renderer& renderer, Camera& camera)
{
	SDL_SetRenderDrawColor(&renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);

	Shape::update(renderer, camera);

	SDL_SetRenderDrawColor(&renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void Asteroid::move()
{
}