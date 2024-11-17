#include "entity/base.h"

#include "models/config.h"
#include "models/math.h"

namespace nigemizu::entity::base {

namespace impl {

namespace config = nigemizu::models::config;
namespace math = nigemizu::models::math;

}  // namespace impl

namespace {

constexpr int kRenderEntityRSize = 8;
constexpr float kRenderEntityVSize = 0.5f;
constexpr float kRenderEntityASize = 8.0f/impl::config::kDefaultFrameRate;

void RenderEntityR(
        const Positional& pos, const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) {
    color_setter(0xFF, 0xFF, 0xFF, 0xFF);
    impl::math::RenderLine(
        pos.r.x - kRenderEntityRSize, pos.r.y,
        pos.r.x + kRenderEntityRSize, pos.r.y,
        plotter);
    impl::math::RenderLine(
        pos.r.x, pos.r.y - kRenderEntityRSize,
        pos.r.x, pos.r.y + kRenderEntityRSize,
        plotter);
}

void RenderEntityV(
        const Positional& pos, const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) {
    color_setter(0xFF, 0xFF, 0x00, 0xFF);
    impl::math::RenderLine(pos.r, pos.r + kRenderEntityVSize*pos.v, plotter);
}

void RenderEntityA(
        const Positional& pos, const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) {
    color_setter(0xFF, 0x00, 0x00, 0xFF);
    impl::math::RenderLine(pos.r, pos.r + kRenderEntityASize*pos.a, plotter);
}

}  // namespace

void Entity::RenderDebugInfo(
        const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) const {
    // TODO: Render the boundary of this entity here in the future.
    // ...
    RenderEntityR(pos_, plotter, color_setter);
    RenderEntityV(pos_, plotter, color_setter);
    RenderEntityA(pos_, plotter, color_setter);
}

}  // namespace nigemizu::entity::base
