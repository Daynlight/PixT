#include "ObjectsUI.h"

inline void PF::ObjectsUI::renderObjectsList(){
  for(size_t i = 0; i < objects->objects.size(); i++){
    ImGui::Text(objects->objects[i]->getName());
    if(ImGui::BeginPopupContextItem(("Object" + std::to_string(i)).c_str())){
      if(ImGui::MenuItem("Delete")){
        delete objects->objects[i];
        objects->objects.remove(i);
        Log::log("Object Deleted");
      };
      if(ImGui::MenuItem("Properties")){
        show_properties = true;
        properties_index = i;
        position = static_cast<ColourBox*>(objects->objects[properties_index])->getPosition();
        Log::log("Object Properties");
      };
      ImGui::EndPopup();
    };
  };
};

inline void PF::ObjectsUI::renderAddColourBox() {
  ImGui::Begin("Add Object", nullptr, ImGuiWindowFlags_MenuBar);

  ImGui::BeginMenuBar();
  if(ImGui::Button("exit")) {add_colour_box = false; Log::log("Add Colour Box Window Closed");}
  ImGui::EndMenuBar();

  ImGui::InputInt("X: ", &position[0]);
  ImGui::InputInt("Y: ", &position[1]);
  ImGui::InputInt("Width: ", &position[2]);
  ImGui::InputInt("Height: ", &position[3]);
  if(position[2] < 0) position[2] = 0;
  if(position[3] < 0) position[3] = 0;

  ImGui::ColorPicker4("##picker", colour.data);

  if(ImGui::Button("Add Object")){
    Vec<char, 4> colourTemp;
    for (size_t i = 0; i < 4; i++) 
      colourTemp[i] = static_cast<char>(colour[i] * 255);

    objects->objects.push(new ColourBox(position, colourTemp));
    Log::inf("Colour Box Added: " + std::to_string((uint8_t)colourTemp[0]) + " " + std::to_string((uint8_t)colourTemp[1]) + " " + std::to_string((uint8_t)colourTemp[2]) + " " + std::to_string((uint8_t)colourTemp[3]));
  };

  ImGui::End();
};

inline void PF::ObjectsUI::renderProperties(){
  if(show_properties){
    if(objects->objects[properties_index]->getType() == iObject::Type::COLOUR_BOX) renderColourBoxProperties();
  }
};

inline void PF::ObjectsUI::renderColourBoxProperties(){
  ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_MenuBar);

  ImGui::BeginMenuBar();
  if(ImGui::Button("exit")) { show_properties = false; Log::log("Properties Window Closed");}
  ImGui::EndMenuBar();

  if(objects->objects[properties_index]->getType() == iObject::Type::COLOUR_BOX){
    ImGui::Text(objects->objects[properties_index]->getName());

    ImGui::InputInt("X: ", &position[0]);
    ImGui::InputInt("Y: ", &position[1]);
    ImGui::InputInt("Width: ", &position[2]);
    ImGui::InputInt("Height: ", &position[3]);

    ImGui::ColorPicker4("##picker", colour.data);

    if(ImGui::Button("Apply")){
      Vec<char, 4> colourTemp;
      for (size_t i = 0; i < 4; i++) 
        colourTemp[i] = static_cast<char>(colour[i] * 255);          
      static_cast<ColourBox*>(objects->objects[properties_index])->setColour(colourTemp);
      Log::inf("Colour Box Colour Applied: " + std::to_string((uint8_t)colourTemp[0]) + " " + std::to_string((uint8_t)colourTemp[1]) + " " + std::to_string((uint8_t)colourTemp[2]) + " " + std::to_string((uint8_t)colourTemp[3]));
    };
    static_cast<ColourBox*>(objects->objects[properties_index])->setPosition(position);
  };

  ImGui::End();
};

void PF::ObjectsUI::render(){
  ImGui::Begin(("Objects (" + std::to_string(id) + ")").c_str(), nullptr, ImGuiWindowFlags_MenuBar);
  if (ImGui::BeginMenuBar()){
    if(ImGui::Button("exit")) {open = false; Log::log("Objects UI Window Closed");}
    if(ImGui::BeginMenu("Add")){
      if(ImGui::MenuItem("ColourBox")) add_colour_box = !add_colour_box;
      ImGui::EndMenu();
    };
    ImGui::EndMenuBar();
  };


  ImGui::Text("Objects:");
  renderObjectsList();
  
  ImGui::End();

  if(add_colour_box) renderAddColourBox();
  else if(show_properties) renderProperties();
};
