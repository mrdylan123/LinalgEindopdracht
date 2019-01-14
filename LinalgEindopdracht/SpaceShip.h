#pragma once
#include "Shape.h"
class SpaceShip : public Shape
{
public:
	SpaceShip();
	~SpaceShip();

	void turnHorizontal(float degrees);
	void turnVertical(float degrees);
	void roll(float degrees);
	void fly();
	void brake();
	void move() override;
	void shoot(Graph* graph);
	void toggleGuideLine();
	const Vector* direction() const { return &direction_; }
	bool destroyed() const { return destroyed_; }
	void setDestroyed(bool destroyed) { destroyed_ = destroyed; }

	void reset();

	void update(SDL_Renderer& renderer, Camera& camera) override;

private:
	Vector direction_;
	bool guideLine_;
	bool destroyed_;
};

