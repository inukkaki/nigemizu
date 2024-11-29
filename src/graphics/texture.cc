#include "graphics/texture.h"

#include "meta/modal.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

namespace nigemizu::graphics::texture {

namespace impl {

namespace modal = nigemizu::meta::modal;

}  // namespace impl

bool Texture::LoadTexture(SDL_Renderer* renderer, const char* file_path) {
    bool succeeds = true;
    FreeTexture();
    SDL_Texture* new_texture = nullptr;
    SDL_Surface* loaded_surface = IMG_Load(file_path);
    if (loaded_surface == nullptr) {
        succeeds = false;
        impl::modal::ShowErrorMessage(
            "Texture Loading Error",
            "Could not load an image file.",
            IMG_GetError());
    } else {
        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (new_texture == nullptr) {
            succeeds = false;
            impl::modal::ShowErrorMessage(
                "Texture Loading Error",
                "Could not create a texture from a surface.",
                SDL_GetError());
        }
        SDL_FreeSurface(loaded_surface);
        loaded_surface = nullptr;
    }
    texture_ = new_texture;
    new_texture = nullptr;
    return succeeds;
}

void Texture::FreeTexture() {
    if (texture_ != nullptr) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}

void Texture::Render(
        SDL_Renderer* renderer, float x, float y,
        const RenderRect& rrect) const {
    SDL_Rect srcrect = {rrect.u, rrect.v, rrect.w, rrect.h};
    SDL_Rect dstrect = {
        static_cast<int>(x + 0.5f) + rrect.x_offset,
        static_cast<int>(y + 0.5f) + rrect.y_offset,
        rrect.w,
        rrect.h
    };
    SDL_RenderCopy(renderer, texture_, &srcrect, &dstrect);
}

}  // namespace nigemizu::graphics::texture
