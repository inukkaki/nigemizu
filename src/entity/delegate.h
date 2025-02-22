#ifndef NIGEMIZU_ENTITY_DELEGATE_H_
#define NIGEMIZU_ENTITY_DELEGATE_H_

#include "entity/base.h"

namespace nigemizu::entity::delegate {

namespace impl {

namespace ebas = nigemizu::entity::base;

}  // namespace impl

class MoveDelegate {
public:
    MoveDelegate() = default;
    virtual ~MoveDelegate() = default;

    virtual void Move(impl::ebas::BaseEntity& self) = 0;
};

class NoMotion final : public MoveDelegate {
public:
    NoMotion() = default;

    void Move(impl::ebas::BaseEntity& self) override { /* NO-OP */ }
};

class GeneralMotion final : public MoveDelegate {
public:
    GeneralMotion() = default;

    void Move(impl::ebas::BaseEntity& self) override;
};

}  // namespace nigemizu::entity::delegate

#endif  // NIGEMIZU_ENTITY_DELEGATE_H_
