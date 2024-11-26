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
void TestBulletPool::Process() const {
    TestBullet& obj = focus();
    obj.Move();
    obj.DoSomething();
    obj.RenderDebugInfo(plotter_, color_setter_);
}

}  // namespace nigemizu::entity::projectile
