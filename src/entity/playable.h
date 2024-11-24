#ifndef NIGEMIZU_ENTITY_PLAYABLE_H_
#define NIGEMIZU_ENTITY_PLAYABLE_H_

#include "entity/entity.h"

namespace nigemizu::entity::playable {

namespace impl {

namespace eent = nigemizu::entity::entity;

}  // namespace impl

class Playable : public impl::eent::Entity {
public:
    Playable() = default;
    virtual ~Playable() = default;
};

}  // namespace nigemizu::entity::playable

#endif  // NIGEMIZU_ENTITY_PLAYABLE_H_
