#include "models/timer.h"

#include "SDL2/SDL.h"

namespace nigemizu::models::timer {

void SimpleTimer::Set() {
    start_time_ = SDL_GetTicks64();
}

unsigned long long int SimpleTimer::GetElapsedTime() const {
    Uint64 elapsed_time = SDL_GetTicks64() - start_time_;
    return elapsed_time;
}

}  // namespace nigemizu::models::timer
