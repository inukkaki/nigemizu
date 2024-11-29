#include "entity/base.h"

#include "meta/assert.h"
#include "models/config.h"
#include "models/math.h"
#include "models/vector.h"

namespace nigemizu::entity::base {

namespace impl {

namespace config = nigemizu::models::config;
namespace math = nigemizu::models::math;
namespace vctr = nigemizu::models::vector;

}  // namespace impl

impl::vctr::Vector2D
        BaseEntity::CalcGravity(const impl::vctr::Vector2D& g) const {
    return phys_.mass*g;
}

impl::vctr::Vector2D BaseEntity::CalcDrag(float fluid_factor) const {
    float drag_coeff = phys_.drag_factor*fluid_factor;
    return -drag_coeff*pos_.v;
}

void BaseEntity::AddForce(const impl::vctr::Vector2D& force) {
    pos_.f += force;
}

void BaseEntity::AssignV(const impl::vctr::Vector2D& v) {
    pos_.v = v;
}

void BaseEntity::AssignR(const impl::vctr::Vector2D& r) {
    pos_.r = r;
}

void BaseEntity::AddR(const impl::vctr::Vector2D& dr) {
    pos_.r += dr;
}

void BaseEntity::UpdateA() {
    pos_.a = pos_.f/phys_.mass;
    pos_.f.Zero();
}

void BaseEntity::UpdateV(float dt) {
    pos_.v += pos_.a*dt;
}

void BaseEntity::UpdateR(float dt) {
    pos_.r += pos_.v*dt;
}

bool BaseEntity::CollidesWith(const BaseEntity& other) const {
    NIGEMIZU_ASSERT(boundary_);
    NIGEMIZU_ASSERT(other.boundary_);
    impl::vctr::Vector2D diff = other.pos_.r - pos_.r;
    return boundary_->CollidesWith(*other.boundary_, diff);
}

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

void BaseEntity::RenderDebugInfo(
        const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) const {
    NIGEMIZU_ASSERT(boundary_);
    color_setter(0xFF, 0xFF, 0xFF, 0xFF);
    boundary_->Render(pos_.r, plotter);
    RenderEntityR(pos_, plotter, color_setter);
    RenderEntityV(pos_, plotter, color_setter);
    RenderEntityA(pos_, plotter, color_setter);
}

}  // namespace nigemizu::entity::base
