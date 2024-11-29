#include "controllers/loop.h"

#include "interfaces/keyboard.h"

#include "SDL2/SDL.h"

// DEBUG
#include <iostream>
#include <memory>
#include "core/singleton.h"
#include "entity/delegate.h"
#include "entity/entity.h"
#include "entity/playable.h"
#include "entity/projectile.h"
#include "interfaces/framerate.h"
#include "models/config.h"
#include "models/math.h"
#include "models/vector.h"

namespace nigemizu::controllers::loop {

namespace impl {

namespace kbd = nigemizu::interfaces::keyboard;

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

    using nigemizu::core::singleton::Singleton;
    using nigemizu::interfaces::keyboard::Keyboard;
    Keyboard& kbd = Singleton::GetInstance<Keyboard>();
    kbd.Clear();

    namespace config = nigemizu::models::config;
    // config::SetFrameRate(30);
    int frame_rate = config::GetFrameRate();
    float frame_duration = config::GetFrameDuration();
    std::cout << frame_rate << " fps" << std::endl;
    std::cout << frame_duration << " s" << std::endl;

    using nigemizu::interfaces::framerate::FrameRateBalancer;
    using nigemizu::interfaces::framerate::FrameRateMeasurer;
    FrameRateBalancer frb(frame_rate);
    FrameRateMeasurer frm;

    double measured_frame_rate = 0.0;

    //
    using nigemizu::entity::playable::Playable;
    using nigemizu::entity::base::PhysicalProperty;
    using nigemizu::models::math::Circle2D;
    // using nigemizu::models::math::NoShape2D;
    namespace dlgt = nigemizu::entity::delegate;
    using nigemizu::entity::playable::KeyConfig;
    using nigemizu::interfaces::keyboard::KeyCode;
    Playable player(
        PhysicalProperty(4.0f, 4.0f),
        std::make_unique<Circle2D>(8.0f),
        // std::make_unique<NoShape2D>(),
        std::make_unique<dlgt::GeneralMotion>(),
        KeyConfig(
            KeyCode::kUp,
            KeyCode::kLeft,
            KeyCode::kRight,
            KeyCode::kDown));
    player.AssignR({16.0f, 16.0f});

    using nigemizu::entity::entity::Entity;
    Entity circle(
        PhysicalProperty(4.0f, 4.0f),
        std::make_unique<Circle2D>(16.0f),
        std::make_unique<dlgt::NoMotion>());
    circle.AssignR({200.0f, 150.0f});

    using nigemizu::models::vector::Vector2D;
    using nigemizu::models::math::LineSegment2D;
    Entity line_segment(
        PhysicalProperty(4.0f, 4.0f),
        std::make_unique<LineSegment2D>(Vector2D(-10.0f, 50.0f)),
        std::make_unique<dlgt::NoMotion>());
    line_segment.AssignR({250.0f, 60.0f});
    //

    using nigemizu::models::math::Plotter;
    using nigemizu::models::math::ColorSetter;
    Plotter plotter = [renderer](int x, int y) -> void {
        SDL_RenderDrawPoint(renderer, x, y);
    };
    ColorSetter color_setter = [renderer](int r, int g, int b, int a) -> void {
        SDL_SetRenderDrawColor(renderer, r, g, b, g);
    };

    //
    using nigemizu::entity::projectile::TestBulletPool;
    TestBulletPool& tbpool = Singleton::GetInstance<TestBulletPool>(100ull);
    int elapsed_frames = 0;
    int count = 0;
    //

    frb.SetTimer();
    frm.SetTimer();
    while (running) {
        running = HandleEvents(kbd);
        if (!running) {
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0x20, 0x40, 0x70, 0xFF);
        SDL_RenderClear(renderer);

        //
        player.AddForce(player.CalcDrag(1.0f));

        player.Control(kbd);
        player.Move();
        player.RenderDebugInfo(plotter, color_setter);

        if (player.CollidesWith(circle)) {
            std::cout << "Circle > Collided!" << std::endl;
        }
        if (player.CollidesWith(line_segment)) {
            std::cout << "Line segment > Collided!" << std::endl;
        }

        circle.RenderDebugInfo(plotter, color_setter);
        line_segment.RenderDebugInfo(plotter, color_setter);
        //

        //
        if (elapsed_frames % 10 == 0) {
            if (tbpool.HasVacancy()) {
                using nigemizu::entity::projectile::TestBullet;
                std::unique_ptr<TestBullet>
                    bullet = std::make_unique<TestBullet>();
                bullet->AssignR({50.0f, 50.0f + 12.0f*count});
                bullet->AddForce({500.0f*(1 + count), 0.0f});
                bullet->Activated();
                tbpool.Create(std::move(bullet));
                ++count;
            }
            if (count > 9) { count = 0; }
        }
        ++elapsed_frames;
        if (elapsed_frames >= 300) { elapsed_frames = 0; }
        tbpool.Update(plotter, color_setter);
        //

        SDL_RenderPresent(renderer);

        if (frm.MeasureFrameRate(measured_frame_rate)) {
            std::cout << measured_frame_rate << " fps" << std::endl;
        }

        kbd.Update();
        frb.Balance();
    }
}

}  // namespace nigemizu::controllers::loop
