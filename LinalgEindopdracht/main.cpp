#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Graph.h"
#include "Vector.h"

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;

		Graph graph{};

		Vector v1{ 0, 0, 0 };
		Vector v2{ 2, 0, 0 };
		Vector v3{ 0, 0, 2 };
		Vector v4{ 2, 0, 2 };
		Vector v5{ 1, 1, 1 };

		/*Vector v1{ 0, 0, 0 };
		Vector v2{ 10, 8, 6 };*/

		// Add the vectors to the list from graph, drawing them afterwards.
		graph.addVector(&v1);
		graph.addVector(&v2);
		graph.addVector(&v3);
		graph.addVector(&v4);
		graph.addVector(&v5);

		Vector startPoint{ 1, 0, 1 };
		Vector endPoint{ 1, 1, 1 };



		if (SDL_CreateWindowAndRenderer(600, 600, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;

			while (!done) {
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				SDL_Delay(10);
				graph.rotateAroundRandomAxis(1, startPoint, endPoint);

				std::vector<std::pair<Vector, Vector>> edges = {
					std::make_pair(v1, v2),
					std::make_pair(v1, v5),
					std::make_pair(v1, v3),
					std::make_pair(v2, v4),
					std::make_pair(v2, v5),
					std::make_pair(v3, v4),
					std::make_pair(v3, v5),
					std::make_pair(v4, v5)
				};

				graph.draw(*renderer);

				SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
				graph.drawShape(*renderer, edges, Graph::View::Front);

				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
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