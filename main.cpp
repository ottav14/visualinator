#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDebug>

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


int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  // Initialize variables
  double window_width = 1920;
  double window_height = 1080;

  double resolution_x = 100.0;
  double resolution_y = resolution_x * window_height / window_width;
  double line_length = 30.0;

  vector<double> offset = {0.0, 0.0};
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
	  
	  // Camera movement binds
	  if(key == "S") move_vector[1] += camera_speed;
	  if(key == "W") move_vector[1] -= camera_speed;
	  if(key == "A") move_vector[0] -= camera_speed;
	  if(key == "D") move_vector[0] += camera_speed;

	  // Camera zoom binds
	  if(key == "J") {
	    resolution_x -= zoom_speed;
	    resolution_y -= zoom_speed;
	  }
	  if(key == "K") {
	    resolution_x += zoom_speed;
	    resolution_y += zoom_speed;
	  }

	  // Normalize movement vector
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
    const double spacing = 100;
    const double scaling_factor_x = window_width / resolution_x;
    const double scaling_factor_y = window_height / resolution_y;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    for(int x=-resolution_x/2 + 1; x<resolution_x/2 ;x++) {
      for(int y=-resolution_y/2 + 1; y<resolution_y/2; y++) {

	double x_prime = zoom * (x + offset[0]); 
	double y_prime = zoom * (y + offset[1]); 

	// ODEs
	double theta = 0.1*time;
	double dx = cos(theta)*x_prime + y_prime;
	double dy = x_prime - sin(theta)*y_prime;

	double magnitude = get_magnitude(dx, dy);
	if(magnitude > 0) {
	  dx *= line_length / magnitude;
	  dy *= line_length / magnitude;
	}

	double screen_x = (x + resolution_x/2) * scaling_factor_x;
	double screen_y = (y + resolution_y/2) * scaling_factor_y;

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

  return 0;

}
