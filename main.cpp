#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
using namespace std;

double get_magnitude(double x, double y) {

  return sqrt(x * x + y * y);

}

string get_key_name(SDL_Event *event) {

  return SDL_GetKeyName(event->key.keysym.sym);

}

int main() {

  // Initialize variables
  int window_width = 1920;
  int window_height = 1080;
  double time = 0.0;
  int resolution = 50;
  double line_length = 20;
  double offset_x = 0;
  double offset_y = 0;
  double camera_speed = 50;

  // Initialize framework
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);

  // Main loop
  bool quit = false;
  SDL_Event event;
  while(!quit) {
    // Event loop
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
	  quit = true;
	  break;

        case SDL_KEYDOWN:

	  string key = get_key_name(&event);
	  
	  if(key == "J") offset_y += camera_speed;
	  if(key == "K") offset_y -= camera_speed;
	  if(key == "H") offset_x -= camera_speed;
	  if(key == "L") offset_x += camera_speed;
	    
	  break;
	
      }
      if (event.type == SDL_QUIT) {
	quit = true;
      }
    }

    // Draw background
    SDL_Rect bg = {0, 0, window_width, window_height};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderFillRect(renderer, &bg);

    // Draw lines
    double scaling_factor_x = window_width / resolution;
    double scaling_factor_y = window_height / resolution;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    for(int x=-0;x<resolution;x++) {
      for(int y=0;y<resolution;y++) {

	double x_prime = x + offset_x;
	double y_prime = y + offset_y;

	double dx = x_prime + y_prime;
	double dy = x_prime + y_prime;

	double magnitude = get_magnitude(dx, dy);
	dx *= line_length / magnitude;
	dy *= line_length / magnitude;

	double screen_x = x * scaling_factor_x;
	double screen_y = y * scaling_factor_y;

	SDL_RenderDrawLine(renderer, screen_x, screen_y, screen_x + dx, screen_y + dy);
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

  std::cout << "Built and executed successfully!" << std::endl;
  return 0;

}
