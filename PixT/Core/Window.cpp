#include "Window.h"

PC::Window::Window(const char* title) {
  Data::Folder settings = Data::Folder("settings/");
  if(!settings.exist()) settings.createFolder();

  if(SDL_Init(SDL_INIT_EVERYTHING)) throw std::runtime_error("SDL Init Error");
  createWindow(title);
  createRenderer();
};

PC::Window::~Window(){
  SDL_Rect window_location = getWindowSizesAndPosition();
  if(window_settings.isEmpty()) window_settings.createFile();
  while(window_settings.size() > 0) window_settings.pop();
  window_settings.push(std::to_string(window_location.x));
  window_settings.push(std::to_string(window_location.y));
  window_settings.push(std::to_string(window_location.w));
  window_settings.push(std::to_string(window_location.h));
  window_settings.push(std::to_string(SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP != 0));
  window_settings.save();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
};

inline void PC::Window::createWindow(const char *title){
  if(window_settings.isEmpty()) {
    window = SDL_CreateWindow(title, WINDOW_POSITION, WINDOW_SIZES, WINDOW_FLAGS);
    if(!window) throw std::runtime_error("Can't create window");
  }
  else{
    window_settings.read();
    
    window = SDL_CreateWindow(title, std::stoi(window_settings[0]), std::stoi(window_settings[1]), 
      std::stoi(window_settings[2]), std::stoi(window_settings[3]), WINDOW_FLAGS);
    if(!window) throw std::runtime_error("Can't create window");
    
    if(window_settings[4] == "1"){
      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    };
  };
};

inline void PC::Window::createRenderer(){
  renderer = SDL_CreateRenderer(window, 0, 0);
  if(!renderer) throw std::runtime_error("Can't create renderer");
};

SDL_Rect PC::Window::getWindowSizesAndPosition(){
  int x, y, w, h;
  SDL_GetWindowPosition(window ,&x, &y);
  SDL_GetWindowSize(window, &w, &h);
  return {x,y,w,h};
};

void PC::Window::windowEvent(const SDL_Event event){
  if(event.type == SDL_QUIT) running = false;
  if(event.type == SDL_KEYDOWN){
    if(event.key.keysym.sym == SDLK_F11) changeFullScreenDesktop();
  };
};

inline void PC::Window::changeFullScreenDesktop(){
  if(SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP != 0) SDL_SetWindowFullscreen(window, 0);
  else SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_Delay(500);
};

bool PC::Window::isRunning() { return running; }
SDL_Renderer *PC::Window::getRenderer() { return renderer; }
SDL_Window *PC::Window::getWindow() { return window; }