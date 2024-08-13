#include "controllers/loop.h"

#include "SDL2/SDL.h"

// DEBUG
#include <iostream>
#include "interfaces/framerate.h"

namespace nigemizu::controllers::loop {

void MainLoop(SDL_Window* window, SDL_Renderer* renderer) {
    // DEBUG
    bool running = true;

    using nigemizu::interfaces::framerate::FrameRateBalancer;
    using nigemizu::interfaces::framerate::FrameRateMeasurer;
    FrameRateBalancer frb(60);
    FrameRateMeasurer frm;

    using nigemizu::models::timer::SimpleTimer;
    SimpleTimer timer;

    double measured_frame_rate = 0.0;

    frb.SetTimer();
    frm.SetTimer();

    timer.Set();

    while (running) {
        if (timer.GetElapsedTime() > 5000) {
            running = false;
        }

        if (frm.MeasureFrameRate(measured_frame_rate)) {
            std::cout << measured_frame_rate << " fps" << std::endl;
        }

        frb.Balance();
    }
}

}  // namespace nigemizu::controllers::loop
