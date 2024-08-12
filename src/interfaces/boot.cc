#include "interfaces/boot.h"

#include "SDL2/SDL.h"

namespace nigemizu::interfaces::boot {

bool InitGui(SDL_Window*& window, SDL_Renderer*& renderer) {
    // TODO: Implement this!
    bool succeeds = false;
    return succeeds;
}

void CloseGui(SDL_Window*& window, SDL_Renderer*& renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    SDL_Quit();
}

}  // namespace nigemizu::interfaces::boot
