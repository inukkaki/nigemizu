#include "entity/projectile.h"

// DEBUG
#include <cstdint>
#include <iostream>

namespace nigemizu::entity::projectile {

// DEBUG
void TestBullet::DoSomething() {
    static bool flag = true;
    uint64_t elapsed_time = timer_.GetElapsedTime();
    if (elapsed_time > 3000ull) {
        activated_ = false;
        if (flag) {
            std::cout << "TestBullet > Deactivated!" << std::endl;
            flag = false;
        }
    }
}

}  // namespace nigemizu::entity::projectile
