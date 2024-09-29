#include "controllers/loop.h"

#include "models/keyboard.h"

#include "SDL2/SDL.h"

// DEBUG
#include <iostream>
#include <memory>
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

    using nigemizu::models::keyboard::KeyConfig;
    using nigemizu::models::keyboard::KeyCode;
    KeyConfig kc = {
        KeyCode::kW,
        KeyCode::kA,
        KeyCode::kD,
        KeyCode::kS,
    };

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
    using nigemizu::models::math::Vector2D;
    using nigemizu::models::math::Circle2D;
    entity::DebugPlayer dp;
    dp.Init();
    entity::Data base_data(
        1.0f,
        Vector2D(320.0f, 240.0f),
        Vector2D(),
        Vector2D(),
        Vector2D(),
        1.0f,
        std::make_unique<Circle2D>(16.0f));
    entity::Entity e2, e3;
    e2.Init(
        std::make_unique<entity::Data>(base_data),
        entity::kAddExternalForce,
        entity::kNotGetGravity,
        entity::kCanGetDrag,
        entity::kApplyExternalForceToA,
        entity::kAddAToV,
        entity::kAddVToR);
    base_data.r += Vector2D(10.0f, 5.0f);
    base_data.boundary.reset(new Circle2D(24.0f));
    e3.Init(
        std::make_unique<entity::Data>(base_data),
        entity::kAddExternalForce,
        entity::kNotGetGravity,
        entity::kCanGetDrag,
        entity::kApplyExternalForceToA,
        entity::kAddAToV,
        entity::kAddVToR);

    using nigemizu::models::math::Plotter;
    using nigemizu::models::math::ColorSetter;
    Plotter plotter = [renderer](int x, int y) -> void {
        SDL_RenderDrawPoint(renderer, x, y);
    };
    ColorSetter color_setter = [renderer](int r, int g, int b, int a) -> void {
        SDL_SetRenderDrawColor(renderer, r, g, b, g);
    };

    frb.SetTimer();
    frm.SetTimer();
    while (running) {
        running = HandleEvents(kbd);
        if (!running) {
            break;
        }

        // DEBUG
        dp.Control(kbd, kc);

        dp.GetGravity({0.0f, 16*9.8f});
        dp.GetDrag(1.0f);
        dp.UpdateA();
        dp.UpdateV(frame_duration);
        dp.UpdateR(frame_duration);

        dp.CollideWith(e2);
        dp.CollideWith(e3);

        e2.GetGravity({0.0f, 16*9.8f});
        e2.GetDrag(1.0f);
        e2.UpdateA();
        e2.UpdateV(frame_duration);
        e2.UpdateR(frame_duration);

        e2.CollideWith(dp);
        e2.CollideWith(e3);

        e3.GetGravity({0.0f, 16*9.8f});
        e3.GetDrag(1.0f);
        e3.UpdateA();
        e3.UpdateV(frame_duration);
        e3.UpdateR(frame_duration);

        e3.CollideWith(dp);
        e3.CollideWith(e2);

        SDL_SetRenderDrawColor(renderer, 0x20, 0x40, 0x70, 0xFF);
        SDL_RenderClear(renderer);

        dp.RenderDebugInfo(plotter, color_setter);
        e2.RenderDebugInfo(plotter, color_setter);
        e3.RenderDebugInfo(plotter, color_setter);

        SDL_RenderPresent(renderer);

        if (frm.MeasureFrameRate(measured_frame_rate)) {
            std::cout << measured_frame_rate << " fps" << std::endl;
        }

        kbd.Update();
        frb.Balance();
    }
}

}  // namespace nigemizu::controllers::loop
