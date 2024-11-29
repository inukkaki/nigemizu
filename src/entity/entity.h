#ifndef NIGEMIZU_ENTITY_ENTITY_H_
#define NIGEMIZU_ENTITY_ENTITY_H_

#include <memory>

#include "entity/base.h"
#include "entity/delegate.h"
#include "meta/assert.h"
#include "models/math.h"

namespace nigemizu::entity::entity {

namespace impl {

namespace ebas = nigemizu::entity::base;
namespace edlg = nigemizu::entity::delegate;
namespace math = nigemizu::models::math;

}  // namespace impl

class Entity : public impl::ebas::BaseEntity {
public:
    Entity(
        const impl::ebas::PhysicalProperty& phys,
        std::unique_ptr<impl::math::Shape2D>&& boundary,
        std::unique_ptr<impl::edlg::MoveDelegate>&& move)
        : impl::ebas::BaseEntity(phys, std::move(boundary)),
          activated_(false),
          move_(std::move(move)) {
        NIGEMIZU_ASSERT(move_);
    }
    virtual ~Entity() = default;

    bool IsActivated() const { return activated_; }

    void Activated()   { activated_ = true; }
    void Deactivated() { activated_ = false; }

    void Move();

private:
    bool activated_;

    std::unique_ptr<impl::edlg::MoveDelegate> move_;
};

}  // namespace nigemizu::entity::entity

#endif  // NIGEMIZU_ENTITY_ENTITY_H_
