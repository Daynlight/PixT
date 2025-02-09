#include "Texture.h"

PF::Core::Renderer::Texture *PF::Core::Renderer::Texture::texture = nullptr;

inline const void PF::Core::Renderer::Texture::addTextureFromFile(const std::string &path) {
  SDL_Surface* surface = IMG_Load(path.c_str());
  SDL_Texture* texture = SDL_CreateTexture(window->getRenderer(), SDL_PIXELFORMAT_RGBA32,
    SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);
  SDL_SetRenderTarget(window->getRenderer(), texture);
  SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
  SDL_SetRenderTarget(window->getRenderer(), NULL);
  textures.push(texture);
  SDL_FreeSurface(surface);
};

const void PF::Core::Renderer::Texture::save() {
  if(file.notExist()) file.createFile();
  file.clear();
  for(int i = 0; i < textures.size(); i++){
    int width, height;
    SDL_QueryTexture(textures[i], NULL, NULL, &width, &height);
    Uint32* pixels = new Uint32[width * height];
    SDL_Rect rect =  SDL_Rect({0,0,width,height});
    int pitch = width * sizeof(Uint32);
    SDL_SetRenderTarget(window->getRenderer(), textures[i]);
    SDL_RenderReadPixels(window->getRenderer(), &rect, SDL_PIXELFORMAT_RGBA32, pixels, pitch);
    SDL_SetRenderTarget(window->getRenderer(), NULL);

    STL::Vector<std::string> record;
    record.push(std::to_string(width));
    record.push(std::to_string(height));
    record.push(std::to_string(pitch));
    for(int y = 0; y < height; y++){
      for(int x = 0; x < width; x++){
        Uint32 pixel = pixels[y * width + x];
        record.push(std::to_string(pixel));
      };
    };
    std::string record_string = record.concat(';');
    file.push(record_string);
    delete[] pixels;
  };
  file.save();
};

const void PF::Core::Renderer::Texture::load() { 
  file.read();
  while(textures.size()) SDL_DestroyTexture(textures.pop());
  STL::Vector<STL::Vector<std::string>> file = this->file.split(';');
  for(size_t i = 0; i < file.size(); i++){

    int width = std::stoi(file[i][0]);
    int height = std::stoi(file[i][1]);
    int pitch = std::stoi(file[i][2]);
    Uint32* pixel = new Uint32[width * height];

    for(int y = 0; y < height; y++){
      for(int x = 0; x < width; x++){
        pixel[y * width + x] = std::stoul(file[i][3 + y * width + x]);
      };
    };

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixel, width, height, 32, pitch, 0, 0, 0, 0);
    SDL_Texture* texture = SDL_CreateTexture(window->getRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);
    SDL_SetRenderTarget(window->getRenderer(), texture);
    SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
    SDL_SetRenderTarget(window->getRenderer(), NULL);

    textures.push(texture);

    SDL_FreeSurface(surface);
    delete[] pixel;
  };
};