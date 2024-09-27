#include "models/entity.h"

#include "models/config.h"
#include "models/keyboard.h"
#include "models/math.h"

namespace nigemizu::models::entity {

namespace impl {

namespace config = nigemizu::models::config;
namespace kbd = nigemizu::models::keyboard;
namespace math = nigemizu::models::math;

}  // namespace impl

void AddExternalForce::ModifyExternalForce(
        Data& self, const impl::math::Vector2D& force) const {
    self.external_force += force;
}

void CanGetGravity::GetGravity(
        Data& self, const impl::math::Vector2D& g) const {
    self.external_force += self.mass*g;
}

void CanGetDrag::GetDrag(Data& self, float fluid_factor) const {
    float k = self.drag_factor*fluid_factor;
    self.external_force -= k*self.v;
}

void ApplyExternalForceToA::UpdateA(Data& self) const {
    self.a = self.external_force/self.mass;
    self.external_force.Zero();
}

void AddAToV::UpdateV(Data& self, float dt) const {
    self.v += self.a*dt;
}

void AddVToR::UpdateR(Data& self, float dt) const {
    self.r += self.v*dt;
}

void Entity::ModifyExternalForce(const impl::math::Vector2D& force) {
    modify_external_force_->ModifyExternalForce(*data_, force);
}

void Entity::GetGravity(const impl::math::Vector2D& g) {
    get_gravity_->GetGravity(*data_, g);
}

void Entity::GetDrag(float fluid_factor) {
    get_drag_->GetDrag(*data_, fluid_factor);
}

void Entity::UpdateA() {
    update_a_->UpdateA(*data_);
}

void Entity::UpdateV(float dt) {
    update_v_->UpdateV(*data_, dt);
}

void Entity::UpdateR(float dt) {
    update_r_->UpdateR(*data_, dt);
}

// DEBUG
void Entity::CollideWith(Entity& other) {
    const Data& od = other.data();
    impl::math::Vector2D offset = od.r - data_->r;
    if (data_->boundary->CollidesWith(*od.boundary, offset)) {
        impl::math::Vector2D force = offset/offset.Length();
        force *= 10.0f*data_->v.Length();
        other.ModifyExternalForce(force);
    }
}

namespace {

constexpr int kEntityCenterCrossSize = 8;

constexpr float kEntityVSize = 0.5f;
constexpr float kEntityASize = 8.0f/config::kDefaultFrameRate;

void RenderEntityCenter(
        const Data& data, const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) {
    color_setter(0xFF, 0xFF, 0xFF, 0xFF);
    impl::math::RenderLine(
        data.r.x - kEntityCenterCrossSize, data.r.y,
        data.r.x + kEntityCenterCrossSize, data.r.y,
        plotter);
    impl::math::RenderLine(
        data.r.x, data.r.y - kEntityCenterCrossSize,
        data.r.x, data.r.y + kEntityCenterCrossSize,
        plotter);
}

void RenderEntityV(
        const Data& data, const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) {
    color_setter(0xFF, 0xFF, 0x00, 0xFF);
    impl::math::RenderLine(data.r, data.r + kEntityVSize*data.v, plotter);
}

void RenderEntityA(
        const Data& data, const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) {
    color_setter(0xFF, 0x00, 0x00, 0xFF);
    impl::math::RenderLine(data.r, data.r + kEntityASize*data.a, plotter);
}

}  // namespace

void Entity::RenderDebugInfo(
        const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) const {
    color_setter(0xFF, 0xFF, 0xFF, 0xFF);
    data_->boundary->Render(data_->r, plotter);
    RenderEntityCenter(*data_, plotter, color_setter);
    RenderEntityV(*data_, plotter, color_setter);
    RenderEntityA(*data_, plotter, color_setter);
};

// DEBUG
void Player::Control(const impl::kbd::Keyboard& kbd) {
    using nigemizu::models::keyboard::KeyCode;
    using nigemizu::models::math::Vector2D;
    Vector2D force;
    if (kbd.Pressing(KeyCode::kA)) {
        force += Vector2D(-1000.0f, 0.0f);
    }
    if (kbd.Pressing(KeyCode::kD)) {
        force += Vector2D(1000.0f, 0.0f);
    }
    if (kbd.Pressing(KeyCode::kW)) {
        force += Vector2D(0.0f, -1000.0f);
    }
    if (kbd.Pressing(KeyCode::kS)) {
        force += Vector2D(0.0f, 1000.0f);
    }
    ModifyExternalForce(force);
}

void Playable::Move(
        const impl::kbd::Keyboard& kbd, const impl::kbd::KeyConfig& kc) {
    impl::math::Vector2D force;
    if (kbd.Pressing(kc.move_up))    { force.y -= 1.0f; }
    if (kbd.Pressing(kc.move_left))  { force.x -= 1.0f; }
    if (kbd.Pressing(kc.move_right)) { force.x += 1.0f; }
    if (kbd.Pressing(kc.move_down))  { force.y += 1.0f; }
    // DEBUG
    ModifyExternalForce(1000.0f*force);
}

}  // namespace nigemizu::models::entity
