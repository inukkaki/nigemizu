#include "meta/boot.h"

#include "SDL2/SDL.h"

#include "meta/modal.h"
#include "models/config.h"

namespace nigemizu::meta::boot {

namespace impl {

namespace modal = nigemizu::meta::modal;

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
    namespace config = nigemizu::models::config;
    window = SDL_CreateWindow(
        config::kTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        config::kWindowWidth, config::kWindowHeight, SDL_WINDOW_SHOWN);
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
    }
    return succeeds;
}

}  // namespace

bool InitGui(SDL_Window*& window, SDL_Renderer*& renderer) {
    bool succeeds = false;
    if (InitSdl(SDL_INIT_VIDEO)) {
        if (CreateWindow(window) && CreateRenderer(window, renderer)) {
            succeeds = true;
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
