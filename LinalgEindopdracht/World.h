#pragma once
#include <vector>
#include <memory>
#include "Shapes/Shape.h"
#include "Camera.h"
#include "Shapes/Planet.h"
#include "Shapes/Asteroid.h"

class Vector;

class World
{
public:
	World();
	~World();

	enum View
	{
		Top,
		Front,
		Side
	};

	void update(SDL_Renderer& renderer);

	std::unique_ptr<Planet>& planet() { return planet_;	}

	const std::vector<std::unique_ptr<Shape>>* getShapes() const { return &shapes_; }
	void addShape(std::unique_ptr<Shape> shape) { shapes_.emplace_back(std::move(shape)); }
	void addPlanet(std::unique_ptr<Planet> planet) { planet_ = std::move(planet); }
	std::vector<std::unique_ptr<Asteroid>>& asteroids() { return asteroids_; }
	void addAsteroid(std::unique_ptr<Asteroid> asteroid) { asteroids_.emplace_back(std::move(asteroid)); }

	Camera& camera() { return camera_; }

	void initializeCamera();

private:
	std::unique_ptr<Planet> planet_;
	std::vector<std::unique_ptr<Asteroid>> asteroids_;

	Camera camera_;
	std::vector<std::unique_ptr<Shape>> shapes_;
};
