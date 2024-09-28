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
    entity::DebugPlayer db;
    db.Init();
    entity::Entity e2;
    e2.Init(
        std::make_unique<entity::Data>(
            1.0f,
            Vector2D(320.0f, 240.0f),
            Vector2D(),
            Vector2D(),
            Vector2D(),
            1.0f,
            std::make_unique<Circle2D>(16.0f)
        ),
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
        db.Control(kbd, kc);

        db.GetGravity({0.0f, 16*9.8f});
        db.GetDrag(1.0f);
        db.UpdateA();
        db.UpdateV(frame_duration);
        db.UpdateR(frame_duration);

        db.CollideWith(e2);

        e2.GetGravity({0.0f, 16*9.8f});
        e2.GetDrag(1.0f);
        e2.UpdateA();
        e2.UpdateV(frame_duration);
        e2.UpdateR(frame_duration);

        e2.CollideWith(db);

        SDL_SetRenderDrawColor(renderer, 0x20, 0x40, 0x70, 0xFF);
        SDL_RenderClear(renderer);

        db.RenderDebugInfo(plotter, color_setter);
        e2.RenderDebugInfo(plotter, color_setter);

        SDL_RenderPresent(renderer);

        if (frm.MeasureFrameRate(measured_frame_rate)) {
            std::cout << measured_frame_rate << " fps" << std::endl;
        }

        kbd.Update();
        frb.Balance();
    }
}

}  // namespace nigemizu::controllers::loop
