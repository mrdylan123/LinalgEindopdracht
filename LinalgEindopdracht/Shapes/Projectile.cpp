#include "Projectile.h"
#include "SpaceShip.h"


Projectile::Projectile(SpaceShip* ship) : Shape(std::vector<Vector>{}, std::vector<std::pair<Vector*, Vector*>>{}, ship->vectors()[2])
{
    Vector end{ *ship->direction() };

    vectors_.emplace_back(ship->position());
    vectors_.emplace_back(end);
    edges_.emplace_back(std::make_pair(&vectors_[0], &vectors_[1]));

    speedVector_ = Vector{ *ship->direction() };
    speedVector_.add(*ship->speedVector());
}


Projectile::~Projectile()
{
}

void Projectile::update(SDL_Renderer& renderer, Camera& camera)
{

    SDL_SetRenderDrawColor(&renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    Shape::update(renderer, camera);

    SDL_SetRenderDrawColor(&renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void Projectile::move()
{
    position_.add(speedVector_);

    for (auto& vector : vectors_)
    {
	vector.add(speedVector_);
    }
}
