#ifndef NIGEMIZU_MODELS_PROJECTILE_H_
#define NIGEMIZU_MODELS_PROJECTILE_H_

// DEBUG
#include <cstddef>
#include <memory>

#include "core/pool.h"
#include "entity/base.h"
#include "entity/delegate.h"
#include "entity/entity.h"
#include "models/math.h"
#include "models/timer.h"

namespace nigemizu::entity::projectile {

namespace impl {

// DEBUG
namespace pool = nigemizu::core::pool;
namespace base = nigemizu::entity::base;
namespace dlgt = nigemizu::entity::delegate;
namespace eent = nigemizu::entity::entity;
namespace math = nigemizu::models::math;
namespace timer = nigemizu::models::timer;

}  // namespace impl

// DEBUG
class TestBullet : public impl::eent::Entity {
public:
    TestBullet()
        : impl::eent::Entity(
            impl::base::PhysicalProperty(1.0f, 0.0f),
            std::make_unique<impl::math::Circle2D>(4.0f),
            std::make_unique<impl::dlgt::GeneralMotion>()) {
        timer_.Set();
    }
    virtual ~TestBullet() = default;

    void DoSomething();

    virtual void Update() { /* NO-OP */ }
        // NOTE: This overload is somehow required to satisfy the constraints
        // of Poolable...
    virtual void Update(
        const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter);

private:
    impl::timer::SimpleTimer timer_;
};

// DEBUG
class TestBulletPool final : public impl::pool::DynamicPool<TestBullet> {
public:
    TestBulletPool(
        size_t size,
        const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter)
        : impl::pool::DynamicPool<TestBullet>(size),
          plotter_(plotter),
          color_setter_(color_setter) {}

private:
    impl::math::Plotter plotter_;
    impl::math::ColorSetter color_setter_;
};

}  // namespace nigemizu::entity::projectile

#endif  // NIGEMIZU_MODELS_PROJECTILE_H_
