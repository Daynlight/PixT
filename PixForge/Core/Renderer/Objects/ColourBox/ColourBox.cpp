#include "ColourBox.h"

PF::Core::Renderer::Objects::ColourBox::ColourBox(const PF::STL::Vec<int, 4> &position, const PF::STL::Vec<char, 4> &colour) : colour(colour) {
  for(unsigned int i = 0; i < 4; i++) this->position[i] = position[i];
};

const std::string PF::Core::Renderer::Objects::ColourBox::save() const {
  STL::Vector<std::string> record;
  record.push(std::to_string(static_cast<int>(getType())));
  for(unsigned int i = 0; i < 4; i++) record.push(std::to_string(position[i]));
  for(unsigned int i = 0; i < 4; i++) record.push(std::to_string(static_cast<int>(colour[i])));
  record.push(name);
  return record.concat(';');
};

const void PF::Core::Renderer::Objects::ColourBox::load(const STL::Vector<std::string> &record){
  for(unsigned int i = 0; i < 4; i++) position[i] = std::stoi(record[i + 1]);
  for(unsigned int i = 0; i < 4; i++) colour[i] = static_cast<char>(std::stoul(record[i + 5]));
  name = record[9];
};

const void PF::Core::Renderer::Objects::ColourBox::render(const Window *window) const {
  SDL_SetRenderDrawColor(window->getRenderer(), colour[0], colour[1], colour[2], colour[3]);
  SDL_Rect tempRect = {position[0], position[1], position[2], position[3]};
  SDL_RenderFillRect(window->getRenderer(), &tempRect);
};