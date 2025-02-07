#pragma once
#include "Ui.h"
#include "STL/Vector.h"
#include "STL/Vec.h"
#include "Objects/ObjectManager.h"

namespace PF{
class ObjectsUI : public iUi{
private:
  const uint8_t id;
  bool open = true;
private:
  ObjectManager *objects;
  Vec<int, 4> position = {0, 0, 0, 0};
  Vec<float, 4> colour = {0, 0, 0, 0};
private:
  bool add_colour_box = false;
  bool show_properties = false;
  size_t properties_index = 0;
private:
  inline void renderObjectsList();
  inline void renderAddColourBox();
  inline void renderProperties();
  inline void renderColourBoxProperties();
public:
  ObjectsUI(const uint8_t id, ObjectManager *objects) : id(id), objects(objects) {};
public:
  uint8_t getID() override { return id; };
  uint8_t getType() override { return Type::OBJECTS_UI; };
  bool isOpen() override { return open; };
  void render() override;
};
};