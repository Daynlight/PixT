#pragma once
#include "../Macro.h"
#include "Settings.h"
#include "Assets.h"
#include "PCRenderer.h"
#include "PCWindow.h"
#include "imgui.h"
#include <cstdlib>

namespace PE{
  class Editor{
    private:
      PC::Window window = PC::Window("PixEditor");    
    public:
      void run();
      void editorEvent();
      bool buildGame(); 
      bool runGame();
  };
};