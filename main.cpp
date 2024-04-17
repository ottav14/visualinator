#include <iostream>
#include <SDL2/SDL.h>

int main() {

  // Initialize framework
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(1920, 1080, 0, &window, &renderer);


  // Initialize variables
  double time = 0.0;

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
    SDL_Rect bg = {0, 0, 1920, 1080};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, &bg);

    // Draw a red rectangle
    SDL_Rect rect = {100 + (int) time, 100, 200, 150};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    SDL_RenderFillRect(renderer, &rect);

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
