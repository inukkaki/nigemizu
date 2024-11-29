#ifndef NIGEMIZU_MODELS_PROJECTILE_H_
#define NIGEMIZU_MODELS_PROJECTILE_H_

// DEBUG
#include <cstddef>
#include <memory>

#include "core/pool.h"
#include "entity/base.h"
#include "entity/delegate.h"
#include "entity/entity.h"
#include "graphics/render.h"
#include "models/shape.h"
#include "models/timer.h"

namespace nigemizu::entity::projectile {

namespace impl {

// DEBUG
namespace pool = nigemizu::core::pool;
namespace ebas = nigemizu::entity::base;
namespace edlg = nigemizu::entity::delegate;
namespace eent = nigemizu::entity::entity;
namespace rndr = nigemizu::graphics::render;
namespace shape = nigemizu::models::shape;
namespace timer = nigemizu::models::timer;

}  // namespace impl

// DEBUG
class TestBullet : public impl::eent::Entity {
public:
    TestBullet()
        : impl::eent::Entity(
            impl::ebas::PhysicalProperty(1.0f, 0.0f),
            std::make_unique<impl::shape::Circle2D>(4.0f),
            std::make_unique<impl::edlg::GeneralMotion>()) {
        timer_.Set();
    }
    virtual ~TestBullet() = default;

    void DoSomething();

    virtual void Update() { /* NO-OP */ }
        // NOTE: This overload is somehow required to satisfy the constraints
        // of Poolable...
    virtual void Update(
        const impl::rndr::Plotter& plotter,
        const impl::rndr::ColorSetter& color_setter);

private:
    impl::timer::SimpleTimer timer_;
};

// DEBUG
using TestBulletPool = impl::pool::DynamicPool<TestBullet>;

}  // namespace nigemizu::entity::projectile

#endif  // NIGEMIZU_MODELS_PROJECTILE_H_
