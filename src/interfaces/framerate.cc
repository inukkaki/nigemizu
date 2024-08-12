#include "interfaces/framerate.h"

#include "SDL2/SDL.h"

namespace nigemizu::interfaces::framerate {

void FrameRateBalancer::SetTimer() {
    timer_.Set();
}

void FrameRateBalancer::Delay() const {
    unsigned long long int elapsed_time = timer_.GetElapsedTime();
    double delay_time = 1000.0/frame_rate_ - elapsed_time;
    if (delay_time > 0.0) {
        SDL_Delay(static_cast<int>(delay_time));
    }
}

}  // nigemizu::interfaces::framerate
