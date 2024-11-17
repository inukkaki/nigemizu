#ifndef NIGEMIZU_ENTITY_DELEGATE_H_
#define NIGEMIZU_ENTITY_DELEGATE_H_

#include "entity/base.h"

namespace nigemizu::entity::delegate {

namespace impl {

namespace base = nigemizu::entity::base;

}  // namespace impl

class UpdateRDelegate {
public:
    UpdateRDelegate() {}
    virtual ~UpdateRDelegate() = default;

    virtual void UpdateR(impl::base::BaseEntity& self, float dt) const = 0;
};

class NotUpdateR final : public UpdateRDelegate {
public:
    NotUpdateR() {}

    void UpdateR(impl::base::BaseEntity& self, float dt) const override {
        /* NO-OP */
    }
};

class AddVToR final : public UpdateRDelegate {
public:
    AddVToR() {}

    void UpdateR(impl::base::BaseEntity& self, float dt) const override;
};

}  // namespace nigemizu::entity::delegate

#endif  // NIGEMIZU_ENTITY_DELEGATE_H_
