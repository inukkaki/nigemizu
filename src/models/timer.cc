#include "models/timer.h"

#include <cstdint>

#include "SDL2/SDL.h"

namespace nigemizu::models::timer {

void SimpleTimer::Set() {
    start_time_ = static_cast<uint64_t>(SDL_GetTicks64());
}

uint64_t SimpleTimer::GetElapsedTime() const {
    uint64_t elapsed_time
        = static_cast<uint64_t>(SDL_GetTicks64()) - start_time_;
    return elapsed_time;
}

}  // namespace nigemizu::models::timer
