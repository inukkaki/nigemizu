#ifndef NIGEMIZU_ENTITY_DELEGATE_H_
#define NIGEMIZU_ENTITY_DELEGATE_H_

#include "entity/base.h"

namespace nigemizu::entity::delegate {

namespace impl {

namespace base = nigemizu::entity::base;

}  // namespace impl

class UpdateADelegate {
public:
    UpdateADelegate() {}
    virtual ~UpdateADelegate() = default;

    virtual void UpdateA(impl::base::BaseEntity& self) const = 0;
};

class NotUpdateA final : public UpdateADelegate {
public:
    NotUpdateA() {}

    void UpdateA(impl::base::BaseEntity& self) const override {
        /* NO-OP */
    }
};

class ApplyFToA final : public UpdateADelegate {
public:
    ApplyFToA() {}

    void UpdateA(impl::base::BaseEntity& self) const override;
};

class UpdateVDelegate {
public:
    UpdateVDelegate() {}
    virtual ~UpdateVDelegate() = default;

    virtual void UpdateV(impl::base::BaseEntity& self, float dt) const = 0;
};

class NotUpdateV final : public UpdateVDelegate {
public:
    NotUpdateV() {}

    void UpdateV(impl::base::BaseEntity& self, float dt) const override {
        /* NO-OP */
    }
};

class AddAToV final : public UpdateVDelegate {
public:
    AddAToV() {}

    void UpdateV(impl::base::BaseEntity& self, float dt) const override;
};

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
