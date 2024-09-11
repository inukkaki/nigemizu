#include "controllers/loop.h"

#include "models/keyboard.h"

#include "SDL2/SDL.h"

// DEBUG
#include <iostream>
#include "interfaces/framerate.h"
#include "models/config.h"
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

    namespace config = nigemizu::models::config;
    //config::SetFrameRate(30);
    int frame_rate = config::GetFrameRate();
    float frame_duration = config::GetFrameDuration();
    std::cout << frame_rate << " fps" << std::endl;
    std::cout << frame_duration << " s" << std::endl;

    using nigemizu::interfaces::framerate::FrameRateBalancer;
    using nigemizu::interfaces::framerate::FrameRateMeasurer;
    FrameRateBalancer frb(frame_rate);
    FrameRateMeasurer frm;

    double measured_frame_rate = 0.0;

    namespace entity = nigemizu::models::entity;
    entity::Player player;

    using nigemizu::models::math::Plotter;
    using nigemizu::models::math::ColorSetter;
    Plotter plotter = [renderer](int x, int y) -> void {
        SDL_RenderDrawPoint(renderer, x, y);
    };
    ColorSetter color_setter = [renderer](int r, int g, int b, int a) -> void {
        SDL_SetRenderDrawColor(renderer, r, g, b, g);
    };

    using nigemizu::models::math::Circle2D;
    Circle2D circle({32, 32}, 16);

    frb.SetTimer();
    frm.SetTimer();
    while (running) {
        running = HandleEvents(kbd);
        if (!running) {
            break;
        }

        // DEBUG
        player.Control(kbd);

        player.GetGravity({0.0f, 16*9.8f});
        player.GetDrag(1.0f);

        player.UpdateA();
        player.UpdateV(frame_duration);
        player.UpdateR(frame_duration);

        SDL_SetRenderDrawColor(renderer, 0x20, 0x40, 0x70, 0xFF);
        SDL_RenderClear(renderer);

        using nigemizu::models::math::RenderCircle;
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        RenderCircle(16, 16, 16, plotter);
        RenderCircle({32, 16}, 16, plotter);
        using nigemizu::models::math::RenderLine;
        RenderLine(31, 0, 31, 31, plotter);
        circle.Render({}, plotter);

        player.RenderDebugInfo(plotter, color_setter);

        SDL_RenderPresent(renderer);

        if (frm.MeasureFrameRate(measured_frame_rate)) {
            std::cout << measured_frame_rate << " fps" << std::endl;
        }

        kbd.Update();
        frb.Balance();
    }
}

}  // namespace nigemizu::controllers::loop
