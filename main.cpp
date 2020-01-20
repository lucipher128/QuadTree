

#include"QuadTree.h"
#include<iostream>
#include<time.h>
#include<random>


#define __HEIGHT 700
#define __WIDTH  800


void cap_framerate(Uint32 start) {
	if ((1000 / 60) > SDL_GetTicks() - start) {
		SDL_Delay((1000 / 60) - (SDL_GetTicks() - start));
	}
}




int main(int argc, char* argv[]) {

	srand(time(NULL));

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = NULL;
	SDL_Renderer* Renderer = NULL;

	window = SDL_CreateWindow("test", 200, 200, __WIDTH, __HEIGHT, SDL_WINDOW_RESIZABLE);
	Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	


	
	

	bool stop = false;
	Uint32 Start;
	SDL_Event e;
	while (!stop) {
		Start = SDL_GetTicks();
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
			{
				stop = true;
			}
		}

		Rectangle* rect = NULL;
		rect = new Rectangle(0, 0, 800, 700);

		QuadTree* test = NULL;
		test = new QuadTree(*rect, 10);

		for (int i = 0; i < 15000; i++)
		{
			Point P(rand() % (int)__WIDTH, rand() % (int)__HEIGHT);
			//std::cout << P.GetX() << "," << P.GetY() << std::endl;
			test->Insert(P);

		}
		test->draw(window, Renderer);
		SDL_RenderPresent(Renderer);
		cap_framerate(Start);
		delete test;
		delete rect;
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 1);
		SDL_RenderClear(Renderer);
	}

	

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Renderer);
	return 0;
}