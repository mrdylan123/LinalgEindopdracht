#pragma once
#include "Shape.h"
class SpaceShip;

class Projectile : public Shape
{
public:
	Projectile(SpaceShip* ship);
	~Projectile();

	void update(SDL_Renderer& renderer, Camera& camera) override;

	void move() override;
};

