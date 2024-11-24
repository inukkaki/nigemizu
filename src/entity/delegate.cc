#include "entity/delegate.h"

#include "entity/base.h"
#include "models/config.h"

namespace nigemizu::entity::delegate {

namespace impl {

namespace base = nigemizu::entity::base;
namespace config = nigemizu::models::config;

}  // namespace impl

void GeneralMotion::Move(impl::base::BaseEntity& self) {
    float dt = impl::config::GetFrameDuration();
    self.UpdateA();
    self.UpdateV(dt);
    self.UpdateR(dt);
}

}  // namespace nigemizu::entity::delegate
