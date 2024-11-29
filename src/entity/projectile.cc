#include "entity/projectile.h"

// DEBUG
#include <cstdint>
#include <iostream>

#include "graphics/render.h"

namespace nigemizu::entity::projectile {

namespace impl {

// DEBUG
namespace rndr = nigemizu::graphics::render;

}  // namespace impl

// DEBUG
void TestBullet::DoSomething() {
    uint64_t elapsed_time = timer_.GetElapsedTime();
    if (elapsed_time > 3000ull) {
        Deactivated();
        std::cout << "TestBullet > Deactivated!" << std::endl;
    }
}

// DEBUG
void TestBullet::Update(
        const impl::rndr::Plotter& plotter,
        const impl::rndr::ColorSetter& color_setter) {
    Move();
    DoSomething();
    RenderDebugInfo(plotter, color_setter);
}

}  // namespace nigemizu::entity::projectile
