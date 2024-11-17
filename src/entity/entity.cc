#include "entity/entity.h"

#include <cassert>

namespace nigemizu::entity::entity {

void Entity::UpdateA() {
    assert(update_a_);
    update_a_->UpdateA(*this);
}

void Entity::UpdateV(float dt) {
    assert(update_v_);
    update_v_->UpdateV(*this, dt);
}

void Entity::UpdateR(float dt) {
    assert(update_r_);
    update_r_->UpdateR(*this, dt);
}

}  // namespace nigemizu::entity::entity
