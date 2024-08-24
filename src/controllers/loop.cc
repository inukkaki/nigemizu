#include "controllers/loop.h"

#include "SDL2/SDL.h"

// DEBUG
#include <iostream>
#include "interfaces/framerate.h"
#include "models/keyboard.h"
#include "models/singleton.h"

namespace nigemizu::controllers::loop {

namespace {

bool HandleEvents() {
    bool running = true;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        default:
            break;
        }
    }
    return running;
}

}  // namespace

void MainLoop(SDL_Window* window, SDL_Renderer* renderer) {
    // DEBUG
    bool running = true;

    using nigemizu::models::singleton::Singleton;
    using nigemizu::models::keyboard::Keyboard;
    Keyboard& kbd = Singleton::GetInstance<Keyboard>();

    using nigemizu::interfaces::framerate::FrameRateBalancer;
    using nigemizu::interfaces::framerate::FrameRateMeasurer;
    FrameRateBalancer frb(60);
    FrameRateMeasurer frm;

    double measured_frame_rate = 0.0;

    frb.SetTimer();
    frm.SetTimer();

    while (running) {
        running = HandleEvents();
        if (!running) {
            break;
        }

        // DEBUG
        std::cout << kbd.ToString() << std::endl;

        if (frm.MeasureFrameRate(measured_frame_rate)) {
            std::cout << measured_frame_rate << " fps" << std::endl;
        }

        frb.Balance();
    }
}

}  // namespace nigemizu::controllers::loop
