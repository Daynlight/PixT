#pragma once
#include <stdexcept>
#include "STL/File/File.h"
#include "STL/Folder/Folder.h"

#include "SDL2/SDL.h"
#include "imgui.h"


// Default Window Settings
#define WINDOW_SIZES 800, 600 
#define WINDOW_POSITION SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
#define WINDOW_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE

namespace PF::Core{
class Window{
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
private:
  STL::File window_settings = STL::File("settings/window_settings.ini");
  bool running = true;
private:
  inline const void changeFullScreenDesktop() const;
  inline const void createWindow(const char* title);
  inline const void createRenderer();
  inline const void save();
  inline const void load();
public:
  Window(const char* title);
  ~Window();
  const void windowEvent(const SDL_Event &event);
  const SDL_Rect getWindowSizesAndPosition() const;
public:
  SDL_Renderer* getRenderer() const { return renderer; };
  SDL_Window* getWindow() const { return window; };
  const bool isRunning() const { return running; };
}; 
}; // namespace PF::Core