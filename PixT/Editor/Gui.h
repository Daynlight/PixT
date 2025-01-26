#pragma once
#include <array>
#include "Tools.h"
#include "../vendor/data/Data.h"
#include "../Core/Window.h"
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_sdl2.h"
#include "../vendor/imgui/imgui_impl_sdlrenderer2.h"

namespace PE{
  struct GuiWindow{ 
    static bool render(uint8_t type = 0);
    inline static bool log();
  };

  class Gui{
    private:
      PC::Window* window;
      Data::File gui_window = Data::File("settings/gui_window.ini");
      inline void gui_window_open(uint8_t type);
      inline void renderDock();
      inline void renderTopBar();
    public:
      Gui(PC::Window* window);
      ~Gui();
      void renderGui();
  };
};