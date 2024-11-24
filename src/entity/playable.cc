#include "entity/playable.h"

#include "interfaces/keyboard.h"

namespace nigemizu::entity::playable {

namespace impl {

namespace kbd = nigemizu::interfaces::keyboard;

}  // namespace impl

void Playable::Control(const impl::kbd::Keyboard& kbd) {
    // TODO: Implement this.
}

}  // namespace nigemizu::entity::playable
