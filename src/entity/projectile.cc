#include "entity/projectile.h"

// DEBUG
#include <cstdint>
#include <iostream>

namespace nigemizu::entity::projectile {

// DEBUG
void TestBullet::DoSomething() {
    uint64_t elapsed_time = timer_.GetElapsedTime();
    if (elapsed_time > 3000ull) {
        activated_ = false;
        std::cout << "TestBullet > Deactivated!" << std::endl;
    }
}

// DEBUG
void TestBullet::Update(
        const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) {
    Move();
    DoSomething();
    RenderDebugInfo(plotter, color_setter);
}

}  // namespace nigemizu::entity::projectile
