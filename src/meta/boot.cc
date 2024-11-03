#include "meta/boot.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "meta/modal.h"
#include "models/config.h"

namespace nigemizu::meta::boot {

namespace impl {

namespace modal = nigemizu::meta::modal;
namespace config = nigemizu::models::config;

}  // namespace impl

namespace {

bool InitSdl(Uint32 flags) {
    bool succeeds = true;
    if (SDL_Init(flags) < 0) {
        succeeds = false;
        impl::modal::ShowErrorMessage(
            "Initialization Error",
            "Could not initialize the SDL library.",
            SDL_GetError());
    }
    return succeeds;
}

bool CreateWindow(SDL_Window*& window) {
    bool succeeds = true;
    int window_width = impl::config::GetWindowWidth();
    int window_height = impl::config::GetWindowHeight();
    window = SDL_CreateWindow(
        impl::config::kTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        succeeds = false;
        impl::modal::ShowErrorMessage(
            "Initialization Error",
            "Could not create a main window.",
            SDL_GetError());
    }
    return succeeds;
}

bool CreateRenderer(SDL_Window*& window, SDL_Renderer*& renderer) {
    bool succeeds = true;
    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        succeeds = false;
        impl::modal::ShowErrorMessage(
            "Initialization Error",
            "Could not create a renderer.",
            SDL_GetError());
    } else {
        float window_scale = impl::config::GetWindowScale();
        SDL_RenderSetScale(renderer, window_scale, window_scale);
    }
    return succeeds;
}

bool InitSdlImage(int flags) {
    bool succeeds = true;
    if (!(IMG_Init(flags) & flags)) {
        succeeds = false;
        impl::modal::ShowErrorMessage(
            "Initialization Error",
            "Could not initialize SDL_image.",
            IMG_GetError());
    }
    return succeeds;
}

}  // namespace

bool InitGui(SDL_Window*& window, SDL_Renderer*& renderer) {
    bool succeeds = false;
    if (InitSdl(SDL_INIT_VIDEO)) {
        if (CreateWindow(window) && CreateRenderer(window, renderer)) {
            if (InitSdlImage(IMG_INIT_PNG)) {
                succeeds = true;
            }
        }
    }
    return succeeds;
}

void CloseGui(SDL_Window*& window, SDL_Renderer*& renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    SDL_Quit();
}

}  // namespace nigemizu::meta::boot
