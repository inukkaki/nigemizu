#include <iostream>

#include "SDL2/SDL.h"

#include "controllers/loop.h"
#include "core/singleton.h"
#include "meta/boot.h"

#if (defined(__WIN32) || defined(__WIN64))
#include "meta/winfunc.h"
#endif

int main(int argc, char* argv[]) {
    #if (defined(__WIN32) || defined(__WIN64))
    using nigemizu::meta::winfunc::ResolveBlurriness;
    ResolveBlurriness();
    #endif

    namespace boot = nigemizu::meta::boot;
    namespace loop = nigemizu::controllers::loop;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool initialized = boot::InitGui(window, renderer);

    if (initialized) {
        loop::MainLoop(window, renderer);
    }

    using nigemizu::core::singleton::Singleton;
    Singleton::Finalize();

    boot::CloseGui(window, renderer);

    return 0;
}
