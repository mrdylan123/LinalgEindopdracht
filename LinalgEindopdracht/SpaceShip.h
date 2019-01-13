#pragma once
#include "Shape.h"
class SpaceShip : public Shape
{
public:
    SpaceShip(std::vector<Vector> vectors, std::vector<std::pair<Vector*, Vector*>> edges, Vector position);
    ~SpaceShip();

    void turnHorizontal(float degrees);
    void turnVertical(float degrees);
    void roll(float degrees);
    void fly();

    void render(SDL_Renderer& renderer, Camera& camera) override;
};

