#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
using namespace std;

vector<double> vector_add( vector<double> a, vector<double> b ) {

  vector<double> output; 

  if(a.size() != b.size()) {
    cerr << "ERROR: Vectors must be the same size when adding." << endl;
    return output;
  }


  return output;

}

double get_magnitude(double x, double y) {

  return sqrt(x * x + y * y);

}

string get_key_name(SDL_Event *event) {

  return SDL_GetKeyName(event->key.keysym.sym);

}


int main() {

  // Initialize variables
  double window_width = 1920;
  double window_height = 1080;

  double resolution_x = 100;
  double resolution_y = resolution_x * window_height / window_width;
  double line_length = 15;

  vector<double> offset = {0, 0};
  double camera_speed = 1.0;
  double zoom_speed = 1.0;
  double time = 0.0;
  double zoom = 1.0;

  // Initialize framework
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);

  // Loop variables
  bool quit = false;
  SDL_Event event;


  // Main loop
  while(!quit) {

    // Event loop
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
	  quit = true;
	  break;

        case SDL_KEYDOWN:

	  string key = get_key_name(&event);

	  vector<double> move_vector = {0, 0};
	  
	  if(key == "S") move_vector[1] += camera_speed;
	  if(key == "W") move_vector[1] -= camera_speed;
	  if(key == "A") move_vector[0] -= camera_speed;
	  if(key == "D") move_vector[0] += camera_speed;

	  if(key == "J") zoom -= zoom_speed;
	  if(key == "K") zoom += zoom_speed;

	  double move_magnitude = get_magnitude(move_vector[0], move_vector[1]);
	  if(move_magnitude > 0) {
	    move_vector[0] /= move_magnitude;
	    move_vector[1] /= move_magnitude;
	  }

	  offset[0] += move_vector[0]; 
	  offset[1] += move_vector[1];

	  break;
	
      }
      if(event.type == SDL_QUIT) {
	quit = true;
      }
    }


    // TODO Interpolate camera position

    // Draw background
    SDL_Rect bg = {0, 0, (int) window_width, (int) window_height};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderFillRect(renderer, &bg);

    // Draw lines
    double scaling_factor_x = window_width / resolution_x;
    double scaling_factor_y = window_height / resolution_y;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    for(int x=1;x<resolution_x;x++) {
      for(int y=1;y<resolution_y;y++) {

	double x_prime = x + offset[0] - resolution_x / 2; 
	double y_prime = y + offset[1] - resolution_y / 2; 

	// ODEs
	double dx = 10*x_prime + y_prime;
	double dy = x_prime - y_prime;

	double magnitude = get_magnitude(dx, dy);
	if(magnitude > 0) {
	  dx *= line_length / log(magnitude);
	  dy *= line_length / log(magnitude);
	}

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
