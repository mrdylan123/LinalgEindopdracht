#pragma once
#include "CollidableShape.h"

class Asteroid : public CollidableShape
{
public:
	Asteroid(const Vector& position);
	~Asteroid();

	void update(SDL_Renderer& renderer, Camera& camera) override;
	void move() override;
};

