#ifndef NIGEMIZU_MODELS_PROJECTILE_H_
#define NIGEMIZU_MODELS_PROJECTILE_H_

// DEBUG
#include <memory>

#include "entity/base.h"
#include "entity/delegate.h"
#include "entity/entity.h"
#include "models/math.h"
#include "models/timer.h"

namespace nigemizu::entity::projectile {

namespace impl {

// DEBUG
namespace base = nigemizu::entity::base;
namespace dlgt = nigemizu::entity::delegate;
namespace eent = nigemizu::entity::entity;
namespace math = nigemizu::models::math;
namespace timer = nigemizu::models::timer;

}  // namespace impl

// DEBUG
class TestBullet final : public impl::eent::Entity {
public:
    TestBullet()
        : impl::eent::Entity(
            impl::base::PhysicalProperty(1.0f, 0.0f),
            std::make_unique<impl::math::Circle2D>(4.0f),
            std::make_unique<impl::dlgt::GeneralMotion>()),
          activated_(true) {}

    bool IsActivated() const { return activated_; }

    void DoSomething();

private:
    bool activated_;
    impl::timer::SimpleTimer timer_;
};

}  // namespace nigemizu::entity::projectile

#endif  // NIGEMIZU_MODELS_PROJECTILE_H_
