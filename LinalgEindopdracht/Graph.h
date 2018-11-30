#pragma once
#include <SDL2/SDL.h>
#include <vector>

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
	void addVector(Vector* vector);
	void drawShape(SDL_Renderer& renderer, std::vector<std::pair<Vector, Vector>>& edges, View view) const;
	void scale(int factorX, int factorY, int factorZ);
	void scaleFromPoint(int factorX, int factorY, int factorZ, Vector& point);
	void translate(int xDirection, int yDirection, int zDirection);
	void rotate(int degrees);
	void rotateFromPoint(int degrees, Vector& point);

private:
	std::vector<Vector*> vectors;
};
