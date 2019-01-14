#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Graph.h"
#include "Vector.h"
#include "Shape.h"
#include "SpaceShip.h"
#include "Planet.h"

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;

		Graph graph{};

		// Spaceship
		std::unique_ptr<SpaceShip> spaceShip = std::make_unique<SpaceShip>();
		SpaceShip* ship = spaceShip.get();

		// Planet
		graph.addPlanet(std::move(std::make_unique<Planet>()));

		// Asteroids
		graph.addAsteroid(std::make_unique<Asteroid>(Vector{ -5 , 0, 0 }));
		graph.addAsteroid(std::make_unique<Asteroid>(Vector{ 5, 1, 1 }));
		graph.addAsteroid(std::make_unique<Asteroid>(Vector{ 3 , 3, 3 }));

		graph.camera().setLookAt(ship);

		// Add the vectors to the list from graph, drawing them afterwards.
		graph.addShape(std::move(spaceShip));

		if (SDL_CreateWindowAndRenderer(600, 600, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;
			bool winMessageShown{ false };
			while (!done) {
				if (ship->destroyed())
				{
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
						"Crash",
						"Je bent tegen een object aangebotst.",
						window);
					ship->reset();
				}

				if(graph.planet() == nullptr)
				{
					if (!winMessageShown)
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
							"Gewonnen",
							"Je hebt de planeet vernietigd.",
							window);
					winMessageShown = true;
					
				}

				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				SDL_Delay(10);

				graph.update(*renderer);

				graph.camera().update(*renderer, graph.camera());

				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_QUIT: done = SDL_TRUE; break;
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym)
						{
						case SDLK_a: ship->turnHorizontal(10); break;
						case SDLK_d: ship->turnHorizontal(-10); break;
						case SDLK_w: ship->turnVertical(-10); break;
						case SDLK_s: ship->turnVertical(10); break;
						case SDLK_q: ship->roll(10); break;
						case SDLK_e: ship->roll(-10); break;
						case SDLK_SPACE: ship->fly(); break;
						case SDLK_LALT: ship->brake(); break;
						case SDLK_RCTRL: ship->shoot(&graph); break;
						case SDLK_h: ship->toggleGuideLine(); break;
						case SDLK_KP_4: graph.camera().rotateHorizontal(-10); break;
						case SDLK_KP_6: graph.camera().rotateHorizontal(10); break;
						case SDLK_KP_8: graph.camera().rotateVertical(-10); break;
						case SDLK_KP_2: graph.camera().rotateVertical(10); break;
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
