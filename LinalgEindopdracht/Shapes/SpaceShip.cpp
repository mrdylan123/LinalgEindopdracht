#include "SpaceShip.h"
#include "../Camera.h"
#include "../World.h"
#include "Projectile.h"


SpaceShip::SpaceShip() : Shape(std::vector<Vector>{
	{ -0.5, 0, 0 },
	{ 0.5, 0, 0 },
	{ 0, 0, -1 },
	{ 0, 0.5, 0 }
}, std::vector<std::pair<Vector*, Vector*>>{}, { 0, 0, 0 }), direction_{ 0, 0, -1 }, guideLine_{ false }, destroyed_(false)
{
		edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[1]));
		edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[2]));
		edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[3]));
		edges_.emplace_back(std::make_pair(&vectors_[1], &vectors_[2]));
		edges_.emplace_back(std::make_pair(&vectors_[1], &vectors_[3]));
		edges_.emplace_back(std::make_pair(&vectors_[2], &vectors_[3]));
}


SpaceShip::~SpaceShip()
{
}

void SpaceShip::turnHorizontal(float degrees)
{
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
	if (speed_ < 1)
		speed_ += 0.1;
}

void SpaceShip::brake()
{
	if (speed_ > 0)
		speed_ -= 0.1;
}

void SpaceShip::move()
{
	Vector direction{ vectors_[2] };

	Vector middlePosition{ position_ };
	direction.subtract(middlePosition);

	direction.normalize();

	direction_ = direction;

	direction.multiply(0.1 * speed_);

	speedVector_ = direction;

	position_.add(speedVector_);

	for (auto& vector : vectors_)
	{
		vector.add(speedVector_);
	}

	if (speed_ > 0)
		speed_ -= 0.001;
}

void SpaceShip::shoot(World* graph)
{
	graph->addShape(std::make_unique<Projectile>(this));
}

void SpaceShip::toggleGuideLine()
{
	guideLine_ = !guideLine_;
}

void SpaceShip::reset()
{
	destroyed_ = false;
	position_ = { 0,0,0 };
	speedVector_ = { 0,0,0 };
	speed_ = 0;
	vectors_ = std::vector<Vector>{
		{ -0.5, 0, 0 },
	{ 0.5, 0, 0 },
	{ 0, 0, -1 },
	{ 0, 0.5, 0 } };

	edges_.clear();

	edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[1]));
	edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[2]));
	edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[3]));
	edges_.emplace_back(std::make_pair(&vectors_[1], &vectors_[2]));
	edges_.emplace_back(std::make_pair(&vectors_[1], &vectors_[3]));
	edges_.emplace_back(std::make_pair(&vectors_[2], &vectors_[3]));
}

void SpaceShip::update(SDL_Renderer& renderer, Camera& camera)
{
	camera.drawInWindow(renderer, position_, vectors_[3]);
	camera.drawInWindow(renderer, position_, vectors_[1]);
	camera.drawInWindow(renderer, position_, vectors_[2]);

	if (guideLine_)
	{
		Vector guideLine{ direction_ };

		guideLine.multiply(100);

		camera.drawInWindow(renderer, position_, guideLine);
	}

	Shape::update(renderer, camera);
}
