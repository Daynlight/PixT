#pragma once
#include "Window/Window.h"
#include "STL/Vec/Vec.h"
#include "STL/Vector/Vector.h"

namespace PF::Core::Renderer::Objects{
class iObject{
public:
  enum Type{
    SPRITE,
    COLOUR_BOX
  };
public:
  virtual const std::string save() const = 0;
  virtual const void load(const STL::Vector<std::string> &record) = 0;
  virtual const void render(const Window *window) const = 0;
public:
  virtual const Type getType() const = 0;
  virtual const std::string getName() const = 0;
  const virtual void setName(const std::string &name) = 0;
  virtual const STL::Vec<int, 4> getPosition() const = 0;
  virtual const void setPosition(const STL::Vec<int, 4> &position) = 0;
};
}; // namespace PF::Core::Renderer::Objects