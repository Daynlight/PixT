#pragma once
#include "../vendor/imgui/imgui.h"
#include "../vendor/data/Data.h"
#include <SDL2/SDL.h>
#include <stdexcept>

// Window Settings
#define WINDOW_SIZES 800, 600 
#define WINDOW_POSITION SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
#define WINDOW_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE

namespace PC {
class Window{
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    Data::File window_settings = Data::File("window_setings.ini");
    const char* title = "";
    bool running = true;
  public:
    Window(const char* title);
    ~Window();
    bool isRunning();
    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();
    void windowEvent(SDL_Event event);
}; 
}