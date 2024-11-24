#ifndef NIGEMIZU_ENTITY_ENTITY_H_
#define NIGEMIZU_ENTITY_ENTITY_H_

#include <memory>

#include "entity/base.h"
#include "entity/delegate.h"
#include "meta/assert.h"
#include "models/math.h"

namespace nigemizu::entity::entity {

namespace impl {

namespace base = nigemizu::entity::base;
namespace dlgt = nigemizu::entity::delegate;
namespace math = nigemizu::models::math;

}  // namespace impl

class Entity : public impl::base::BaseEntity {
public:
    Entity(
        const impl::base::PhysicalProperty& phys,
        std::unique_ptr<impl::math::Shape2D>&& boundary,
        std::unique_ptr<impl::dlgt::MoveDelegate>&& move)
        : impl::base::BaseEntity(phys, std::move(boundary)),
          move_(std::move(move)) {
        NIGEMIZU_ASSERT(move_);
    }
    virtual ~Entity() = default;

    void Move();

private:
    std::unique_ptr<impl::dlgt::MoveDelegate> move_;
};

}  // namespace nigemizu::entity::entity

#endif  // NIGEMIZU_ENTITY_ENTITY_H_
