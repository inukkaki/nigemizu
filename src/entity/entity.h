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
    Entity(
        std::unique_ptr<impl::dlgt::UpdateADelegate>&& update_a,
        std::unique_ptr<impl::dlgt::UpdateVDelegate>&& update_v,
        std::unique_ptr<impl::dlgt::UpdateRDelegate>&& update_r)
        : update_a_(std::move(update_a)),
          update_v_(std::move(update_v)),
          update_r_(std::move(update_r)) {}
    virtual ~Entity() = default;

    void UpdateA();
    void UpdateV(float dt);
    void UpdateR(float dt);

private:
    std::unique_ptr<impl::dlgt::UpdateADelegate> update_a_;
    std::unique_ptr<impl::dlgt::UpdateVDelegate> update_v_;
    std::unique_ptr<impl::dlgt::UpdateRDelegate> update_r_;
};

}  // namespace nigemizu::entity::entity

#endif  // NIGEMIZU_ENTITY_ENTITY_H_
