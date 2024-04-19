#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
using namespace std;

double get_magnitude(double x, double y) {

  return sqrt(x * x + y * y);

}

int main() {

  // Initialize variables
  int window_width = 1920;
  int window_height = 1080;
  double time = 0.0;
  int resolution = 50;
  double line_length = 20;

  // Initialize framework
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);

  // Main loop
  bool quit = false;
  SDL_Event event;
  while(!quit) {
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
	quit = true;
      }
    }

    // Draw background
    SDL_Rect bg = {0, 0, window_width, window_height};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderFillRect(renderer, &bg);

    // Draw lines
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    for(int i=0;i<resolution;i++) {
      for(int j=0;j<resolution;j++) {

	double x1 = i * window_width / resolution;
	double y1 = j * window_height / resolution;
	double magnitude = get_magnitude(x1, y1);

	double x2 = x1 + line_length * x1 / magnitude;
	double y2 = y1 + line_length * y1 / magnitude;

	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
      }
    }

    // Update the window
    SDL_RenderPresent(renderer);

    // Update time
    time += 0.1;
  }

  // Clean up resources
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  std::cout << "Ran successfully!" << std::endl;
  return 0;

}
