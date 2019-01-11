#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "Shape.h"
#include "Camera.h"

class Vector;

class Graph
{
public:
	Graph();
	~Graph();

	enum View
	{
		Top,
		Front,
		Side
	};

	void draw(SDL_Renderer& renderer);

	const std::vector<std::unique_ptr<Shape>>* getShapes() const { return &shapes_; }
	void addShape(std::unique_ptr<Shape> shape) { shapes_.emplace_back(std::move(shape)); }

	Camera& camera() { return camera_; }

	void initializeCamera();

private:
	Camera camera_;
	std::vector<std::unique_ptr<Shape>> shapes_;
};
