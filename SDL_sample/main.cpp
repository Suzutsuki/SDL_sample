#include <cstdio>
#include <cstdlib>
#include "SDL.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	atexit(SDL_Quit);

	auto window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (!window) {
		fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		return EXIT_FAILURE;
	}

	auto quit = false;
	while (!quit) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return EXIT_SUCCESS;
}
