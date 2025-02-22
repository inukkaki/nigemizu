#ifndef NIGEMIZU_GRAPHICS_TEXTURE_H_
#define NIGEMIZU_GRAPHICS_TEXTURE_H_

#include <memory>

#include "SDL2/SDL.h"

namespace nigemizu::graphics::texture {

struct RenderRect {
    int u;
    int v;
    int w;
    int h;
    int x_offset;
    int y_offset;
};

class Texture {
public:
    Texture() : texture_(nullptr) {}
    ~Texture() {
        FreeTexture();
    }

    bool LoadTexture(SDL_Renderer* renderer, const char* file_path);
    void FreeTexture();

    void Render(
        SDL_Renderer* renderer, float x, float y,
        const RenderRect& rrect) const;

private:
    SDL_Texture* texture_;
};

}  // namespace nigemizu::graphics::texture

#endif  // NIGEMIZU_GRAPHICS_TEXTURE_H_
