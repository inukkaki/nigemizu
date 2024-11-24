#ifndef NIGEMIZU_ENTITY_ENTITY_H_
#define NIGEMIZU_ENTITY_ENTITY_H_

#include <memory>

#include "entity/base.h"
#include "entity/delegate.h"

namespace nigemizu::entity::entity {

namespace impl {

namespace base = nigemizu::entity::base;
namespace dlgt = nigemizu::entity::delegate;

}  // namespace impl

class Entity : public impl::base::BaseEntity {
public:
    explicit Entity(
        std::unique_ptr<impl::dlgt::MoveDelegate>&& move)
        : move_(std::move(move)) {}
    virtual ~Entity() = default;

    void UpdatePosition();

    void Move();

private:
    std::unique_ptr<impl::dlgt::MoveDelegate> move_;
};

}  // namespace nigemizu::entity::entity

#endif  // NIGEMIZU_ENTITY_ENTITY_H_
