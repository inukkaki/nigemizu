#include "entity/delegate.h"

#include "entity/base.h"

namespace nigemizu::entity::delegate {

namespace impl {

namespace base = nigemizu::entity::base;

}  // namespace impl

void AddAToV::UpdateV(impl::base::BaseEntity& self, float dt) const {
    impl::base::Positional& pos = self.pos();
    pos.v += pos.a*dt;
}

void AddVToR::UpdateR(impl::base::BaseEntity& self, float dt) const {
    impl::base::Positional& pos = self.pos();
    pos.r += pos.v*dt;
}

}  // namespace nigemizu::entity::delegate
