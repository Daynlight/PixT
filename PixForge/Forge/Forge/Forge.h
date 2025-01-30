#pragma once
#include "Window/Window.h"
#include "Render/Render.h"
#include "Gui/Gui.h"

#include "Tools/Tools.h"
#include "Settings.h"

#include "Sandbox.h"

namespace PF{
  class Forge{
    private:
      Window window;
      Sandbox sandbox;
      Gui gui;
    private:
      Folder assets_folder = Folder("assets");
    private:
      inline void events();
    public:
      Forge();
      ~Forge();
      void run();
  };
};