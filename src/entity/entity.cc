#include "entity/entity.h"

#include "meta/assert.h"
#include "models/config.h"

namespace nigemizu::entity::entity {

namespace impl {

namespace config = nigemizu::models::config;

}  // namespace impl

void Entity::UpdatePosition() {
    // NOTE: This function might contain more processes in the future.
    float dt = impl::config::GetFrameDuration();
    UpdateA();
    UpdateV(dt);
    UpdateR(dt);
}

void Entity::Move() {
    NIGEMIZU_ASSERT(move_);
    move_->Move(*this);
}

}  // namespace nigemizu::entity::entity
