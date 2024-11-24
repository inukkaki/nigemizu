#ifndef NIGEMIZU_ENTITY_DELEGATE_H_
#define NIGEMIZU_ENTITY_DELEGATE_H_

#include "entity/base.h"

namespace nigemizu::entity::delegate {

namespace impl {

namespace base = nigemizu::entity::base;

}  // namespace impl

class MoveDelegate {
public:
    MoveDelegate() = default;
    virtual ~MoveDelegate() = default;

    virtual void Move(impl::base::BaseEntity& self) = 0;
};

class NoMotion final : public MoveDelegate {
public:
    NoMotion() = default;

    void Move(impl::base::BaseEntity& self) override { /* NO-OP */ }
};

}  // namespace nigemizu::entity::delegate

#endif  // NIGEMIZU_ENTITY_DELEGATE_H_
