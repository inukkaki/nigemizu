#include <iostream>

#include "SDL2/SDL.h"

#include "controllers/loop.h"
#include "interfaces/boot.h"
#include "models/singleton.h"

int main(int argc, char* argv[]) {
    namespace boot = nigemizu::interfaces::boot;
    namespace loop = nigemizu::controllers::loop;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool initialized = boot::InitGui(window, renderer);

    if (initialized) {
        loop::MainLoop(window, renderer);
    }

    using nigemizu::models::singleton::Singleton;
    Singleton::Finalize();

    boot::CloseGui(window, renderer);

    return 0;
}
