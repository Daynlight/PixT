#pragma once
#include "../Settings.h"
#include "../PixCore/PixCore.h"

namespace PC{
class Editor{
  private:
    Window *window;
  public:
    Editor(Window *window);
    ~Editor();
    void run();
};

}