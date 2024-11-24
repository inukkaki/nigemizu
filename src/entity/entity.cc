#include "entity/entity.h"

#include "meta/assert.h"

namespace nigemizu::entity::entity {

void Entity::Move() {
    NIGEMIZU_ASSERT(move_);
    move_->Move(*this);
}

}  // namespace nigemizu::entity::entity
