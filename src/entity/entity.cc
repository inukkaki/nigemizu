#include "entity/entity.h"

#include <cassert>

namespace nigemizu::entity::entity {

void Entity::UpdateR(float dt) {
    assert(update_r_);
    update_r_->UpdateR(*this, dt);
}

}  // namespace nigemizu::entity::entity
