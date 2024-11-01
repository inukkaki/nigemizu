#ifndef NIGEMIZU_INTERFACES_TEXTURE_H_
#define NIGEMIZU_INTERFACES_TEXTURE_H_

#include <memory>

#include "SDL2/SDL.h"

namespace nigemizu::interfaces::texture {

class Texture {
public:
    Texture() : texture_(nullptr) {}
    ~Texture() {
        FreeTexture();
    }

    bool LoadTexture(SDL_Renderer* renderer, const char* file_path);
    void FreeTexture();

private:
    SDL_Texture* texture_;
};

}  // namespace nigemizu::interfaces::texture

#endif  // NIGEMIZU_INTERFACES_TEXTURE_H_
