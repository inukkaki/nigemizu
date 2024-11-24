#ifndef NIGEMIZU_ENTITY_ENTITY_H_
#define NIGEMIZU_ENTITY_ENTITY_H_

#include "entity/base.h"

namespace nigemizu::entity::entity {

namespace impl {

namespace base = nigemizu::entity::base;

}  // namespace impl

class Entity : public impl::base::BaseEntity {
public:
    Entity() = default;
    virtual ~Entity() = default;
};

}  // namespace nigemizu::entity::entity

#endif  // NIGEMIZU_ENTITY_ENTITY_H_
