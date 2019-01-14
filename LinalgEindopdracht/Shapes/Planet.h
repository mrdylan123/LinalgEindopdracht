#pragma once
#include "CollidableShape.h"

class Planet : public CollidableShape
{
public:
	Planet();
	~Planet();

	void move() override;
	bool collidesWith(Shape& shape) override;


	int& hits() { return hits_; }

	void update(SDL_Renderer& renderer, Camera& camera) override;


private:
	std::pair<double, double> sizeRange_;
	bool shrinking_;
	int hits_;
};


