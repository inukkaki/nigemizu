#include "entity/entity.h"

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

}  // namespace nigemizu::entity::entity
