#include "entity/playable.h"

#include "interfaces/keyboard.h"
#include "models/math.h"

// DEBUG
#include <memory>
#include "core/singleton.h"
#include "entity/projectile.h"

namespace nigemizu::entity::playable {

namespace impl {

namespace kbd = nigemizu::interfaces::keyboard;
namespace math = nigemizu::models::math;

// DEBUG
namespace sngl = nigemizu::core::singleton;
namespace prjc = nigemizu::entity::projectile;

}  // namespace impl

void Playable::Transfer(const impl::kbd::Keyboard& kbd) {
    impl::math::Vector2D force;
    if (kbd.Pressing(kc_.transfer_up))    { force.y -= 1.0f; }
    if (kbd.Pressing(kc_.transfer_left))  { force.x -= 1.0f; }
    if (kbd.Pressing(kc_.transfer_right)) { force.x += 1.0f; }
    if (kbd.Pressing(kc_.transfer_down))  { force.y += 1.0f; }
    // TODO: Customize the coefficient of force.
    AddForce(1000.0f*force);
}

// DEBUG
void Playable::Attack(const impl::kbd::Keyboard& kbd) {
    if (kbd.Presses(impl::kbd::KeyCode::kZ)) {
        impl::prjc::TestBulletPool& pool =
            impl::sngl::Singleton::GetInstance<impl::prjc::TestBulletPool>();
        if (pool.HasVacancy()) {
            std::unique_ptr<impl::prjc::TestBullet>
                bullet = std::make_unique<impl::prjc::TestBullet>();
            bullet->AssignR(pos().r);
            bullet->AddForce({20000.0f, 0.0f});
            bullet->Activated();
            pool.Create(std::move(bullet));
        }
    }
}

void Playable::Control(const impl::kbd::Keyboard& kbd) {
    // TODO: Implement this.
    Transfer(kbd);
        // DEBUG
        Attack(kbd);
}

}  // namespace nigemizu::entity::playable
