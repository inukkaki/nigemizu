#include <iostream>

#include "SDL2/SDL.h"

#define NIGEMIZU_USE_GUI_ASSERT

#include "controllers/loop.h"
#include "core/singleton.h"
#include "meta/boot.h"

#if (defined(__WIN32) || defined(__WIN64))
#include "meta/winfunc.h"
#endif

namespace impl {

namespace loop = nigemizu::controllers::loop;
namespace singleton = nigemizu::core::singleton;
namespace boot = nigemizu::meta::boot;

}  // namespace impl

int main(int argc, char* argv[]) {
    #if (defined(__WIN32) || defined(__WIN64))
    using nigemizu::meta::winfunc::ResolveBlurriness;
    ResolveBlurriness();
    #endif

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool initialized = impl::boot::InitGui(window, renderer);

    if (initialized) {
        impl::loop::MainLoop(window, renderer);
    }

    impl::singleton::Singleton::Finalize();

    impl::boot::CloseGui(window, renderer);

    return 0;
}
