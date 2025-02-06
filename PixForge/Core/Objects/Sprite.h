#pragma once
#include "Object.h"
#include "SDL2/SDL.h"
#include "STL/Vec.h"
#include "Window/Window.h"

namespace PF{
  class Sprite : public Object{
    private:
      SDL_Texture *texture;
      Vec<int, 2> position;
    public:
      void render(Window *window) override;
  };
}