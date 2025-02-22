#include "controllers/loop.h"

#include "interfaces/keyboard.h"

#include "SDL2/SDL.h"

// DEBUG
#include <iostream>
#include <memory>
#include "core/singleton.h"
#include "entity/delegate.h"
#include "entity/playable.h"
#include "entity/projectile.h"
#include "interfaces/framerate.h"
#include "models/config.h"
#include "models/shape.h"

namespace nigemizu::controllers::loop {

namespace impl {

namespace kbd = nigemizu::interfaces::keyboard;

// DEBUG
namespace sngl = nigemizu::core::singleton;
namespace ebas = nigemizu::entity::base;
namespace edlg = nigemizu::entity::delegate;
namespace eply = nigemizu::entity::playable;
namespace eprj = nigemizu::entity::projectile;
namespace fr = nigemizu::interfaces::framerate;
namespace config = nigemizu::models::config;
namespace shape = nigemizu::models::shape;

}  // namespace impl

namespace {

bool HandleEvents(impl::kbd::Keyboard& kbd) {
    bool proceeds = true;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            proceeds = false;
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
    return proceeds;
}

}  // namespace

void MainLoop(SDL_Window* window, SDL_Renderer* renderer) {
    // DEBUG
    bool proceeds = true;

    int frame_rate = impl::config::GetFrameRate();
    impl::fr::FrameRateBalancer frb(frame_rate);
    impl::fr::FrameRateMeasurer frm;
    double measured_frame_rate;

    impl::kbd::Keyboard& kbd =
        impl::sngl::Singleton::GetInstance<impl::kbd::Keyboard>();

    impl::eprj::TestBulletPool& tb_pool =
        impl::sngl::Singleton::GetInstance<impl::eprj::TestBulletPool>(100ull);
    impl::eply::Playable player(
        impl::ebas::PhysicalProperty(4.0f, 4.0f),
        std::make_unique<impl::shape::Circle2D>(8.0f),
        std::make_unique<impl::edlg::GeneralMotion>(),
        impl::eply::KeyConfig(
            impl::kbd::KeyCode::kUp,
            impl::kbd::KeyCode::kLeft,
            impl::kbd::KeyCode::kRight,
            impl::kbd::KeyCode::kDown));

    player.AssignR({80.0f, 40.0f});

    kbd.Clear();

    frb.SetTimer();
    frm.SetTimer();
    while (proceeds) {
        proceeds = HandleEvents(kbd);
        if (!proceeds) {
            break;
        }

        // --- CALC AND RENDERING START ---
        SDL_SetRenderDrawColor(renderer, 0x20, 0x40, 0x70, 0xFF);
        SDL_RenderClear(renderer);

        player.AddForce(player.CalcDrag(1.0f));
        player.Control(kbd);
        player.Move();
        player.RenderDebugInfo();

        tb_pool.Update();

        SDL_RenderPresent(renderer);
        // --- CALC AND RENDERING END ---

        kbd.Update();

        measured_frame_rate = frm.MeasureFrameRate();
        if (measured_frame_rate > 0.0) {
            std::cout << measured_frame_rate << " FPS" << std::endl;
        }
        frb.Balance();
    }
}

}  // namespace nigemizu::controllers::loop
