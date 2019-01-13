#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Graph.h"
#include "Vector.h"
#include "Shape.h"
#include "SpaceShip.h"

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Graph graph{};

	Vector v1{ -0.5, 0, 0 };
	Vector v2{ 0.5, 0, 0 };
	Vector v3{ 0, 0, -1 };
	Vector v4{ 0, 0.5, 0 };

	std::vector<Vector> vectors{ {v1, v2, v3, v4} };
	std::vector<std::pair<Vector*, Vector*>> edges{ {
			std::make_pair(&vectors[0], &vectors[1]),
			std::make_pair(&vectors[0], &vectors[2]),
			std::make_pair(&vectors[0], &vectors[3]),
			std::make_pair(&vectors[1], &vectors[2]),
			std::make_pair(&vectors[1], &vectors[3]),
			std::make_pair(&vectors[2], &vectors[3])
		} };
	Vector position{ 0, 0, 0 };

	std::unique_ptr<SpaceShip> spaceShip = std::make_unique<SpaceShip>(std::move(vectors), std::move(edges), std::move(position));

	SpaceShip* ship = spaceShip.get();

	graph.camera().setLookAt(ship);

	// Add the vectors to the list from graph, drawing them afterwards.
	graph.addShape(std::move(spaceShip));

	if (SDL_CreateWindowAndRenderer(600, 600, 0, &window, &renderer) == 0) {
	    SDL_bool done = SDL_FALSE;

	    while (!done) {
		SDL_Event event;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		SDL_Delay(10);

		graph.draw(*renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event)) {
		    switch (event.type) {
		    case SDL_QUIT: done = SDL_TRUE; break;
		    case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_a: ship->turnHorizontal(10); break;
			case SDLK_d: ship->turnHorizontal(-1); break;
			case SDLK_w: ship->turnVertical(-1); break;
			case SDLK_s: ship->turnVertical(1); break;
			case SDLK_q: ship->roll(1); break;
			case SDLK_e: ship->roll(-1); break;
			case SDLK_SPACE: ship->fly(); break;
			case SDLK_UP: graph.camera().moveY(0.1); break;
			case SDLK_DOWN: graph.camera().moveY(-0.1); break;
			case SDLK_LEFT: graph.camera().moveX(-0.1); break;
			case SDLK_RIGHT: graph.camera().moveX(0.1); break;
			}
		    }
		}
	    }
	}

	if (renderer) {
	    SDL_DestroyRenderer(renderer);
	}
	if (window) {
	    SDL_DestroyWindow(window);
	}
    }
    SDL_Quit();
    return 0;
}
