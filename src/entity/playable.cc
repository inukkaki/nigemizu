#include "entity/playable.h"

#include "interfaces/keyboard.h"
#include "models/math.h"

namespace nigemizu::entity::playable {

namespace impl {

namespace kbd = nigemizu::interfaces::keyboard;
namespace math = nigemizu::models::math;

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

void Playable::Control(const impl::kbd::Keyboard& kbd) {
    // TODO: Implement this.
    Transfer(kbd);
}

}  // namespace nigemizu::entity::playable
