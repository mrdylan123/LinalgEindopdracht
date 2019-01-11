#include "Graph.h"
#include "Matrix.h"
#define _USE_MATH_DEFINES
#include "Vector.h"
#include "Shape.h"

Graph::Graph() : camera_{ this }
{
	
}


Graph::~Graph()
{
}

void Graph::draw(SDL_Renderer& renderer)
{
	SDL_SetRenderDrawColor(&renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(&renderer, 0, 300, 600, 300); // X-axis
	SDL_RenderDrawLine(&renderer, 300, 0, 300, 600); // Y-axis

	// Get all vectors and draw them aswell
	for (auto& shape : shapes_)
	{
		shape->render(renderer, camera_);
	}
}

void Graph::initializeCamera()
{
	camera_.lookatMatrix();
}
