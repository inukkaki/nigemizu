#include "controllers/loop.h"

#include "models/keyboard.h"

#include "SDL2/SDL.h"

// DEBUG
#include <iostream>
#include "interfaces/framerate.h"
#include "models/entity.h"
#include "models/math.h"
#include "models/singleton.h"

namespace nigemizu::controllers::loop {

namespace impl {

namespace kbd = nigemizu::models::keyboard;

}  // namespace impl

namespace {

bool HandleEvents(impl::kbd::Keyboard& kbd) {
    bool running = true;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            kbd.HandleKeyDown(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            kbd.HandleKeyUp(event.key.keysym.sym);
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
    kbd.Clear();

    using nigemizu::interfaces::framerate::FrameRateBalancer;
    using nigemizu::interfaces::framerate::FrameRateMeasurer;
    FrameRateBalancer frb(60);
    FrameRateMeasurer frm;

    double measured_frame_rate = 0.0;

    namespace entity = nigemizu::models::entity;
    using nigemizu::models::math::Vector2D;
    entity::Data data;
    data.r = Vector2D(5.0f, 4.0f);
    entity::Entity ent(data);

    frb.SetTimer();
    frm.SetTimer();
    while (running) {
        running = HandleEvents(kbd);
        if (!running) {
            break;
        }

        // DEBUG
        SDL_SetRenderDrawColor(renderer, 0x20, 0x40, 0x70, 0xFF);
        SDL_RenderClear(renderer);
        ent.Display(renderer);
        SDL_RenderPresent(renderer);

        if (frm.MeasureFrameRate(measured_frame_rate)) {
            std::cout << measured_frame_rate << " fps" << std::endl;
        }

        kbd.Update();
        frb.Balance();
    }
}

}  // namespace nigemizu::controllers::loop
