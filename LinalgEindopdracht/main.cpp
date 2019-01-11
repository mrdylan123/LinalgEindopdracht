#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Graph.h"
#include "Vector.h"
#include "Shape.h"

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        Graph graph{};

        Vector v1{ 0, 0, 0 };
        Vector v2{ 1, 0, 0 };
        Vector v3{ 0, 0, 1 };
        Vector v4{ 1, 0, 1 };
        Vector v5{ 0.5, 0.5, 0 };

        std::vector<Vector> vectors{ {v1, v2, v3, v4, v5} };
		std::vector<std::pair<Vector*, Vector*>> edges{ {
				std::make_pair(&vectors[0], &vectors[1]),
				std::make_pair(&vectors[0], &vectors[4]),
				std::make_pair(&vectors[0], &vectors[2]),
				std::make_pair(&vectors[1], &vectors[3]),
				std::make_pair(&vectors[1], &vectors[4]),
				std::make_pair(&vectors[2], &vectors[3]),
				std::make_pair(&vectors[2], &vectors[4]),
				std::make_pair(&vectors[3], &vectors[4])
			} };
		Vector position{ 0, 0, 0 };

        std::unique_ptr<Shape> spaceShip = std::make_unique<Shape>(std::move(vectors), std::move(edges), std::move(position));

        /*Vector v1{ 0, 0, 0 };
        Vector v2{ 10, 8, 6 };*/

        // Add the vectors to the list from graph, drawing them afterwards.
        graph.addShape(std::move(spaceShip));

		//graph.initializeCamera();

        Vector startPoint{ 1, 0, 1 };
        Vector endPoint{ 1, 1, 1 };

        Vector w{ 0, 1, 0 };
        Vector v{ 1, 0, 0 };

        if (SDL_CreateWindowAndRenderer(600, 600, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_Delay(10);
				//graph.camera().position().setZ(graph.camera().position().z() - 0.1);
				//graph.camera().position().setY(graph.camera().position().y() + 0.001);
				//graph.camera().position().setX(graph.camera().position().x() + 0.001);
                graph.draw(*renderer);

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

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
