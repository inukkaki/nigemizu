#include "models/entity.h"

#include "models/math.h"

// DEBUG
#include "SDL2/SDL.h"
#include "models/keyboard.h"

namespace nigemizu::models::entity {

namespace impl {

// DEBUG
namespace kbd = nigemizu::models::keyboard;

namespace math = nigemizu::models::math;

}  // namespace impl

void AddExternalForce::ModifyExternalForce(
        Data& self, const impl::math::Vector2D& force) const {
    self.external_force += force;
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
    modify_external_force_->ModifyExternalForce(data_, force);
}

void Entity::UpdateA() {
    update_a_->UpdateA(data_);
}

void Entity::UpdateV(float dt) {
    update_v_->UpdateV(data_, dt);
}

void Entity::UpdateR(float dt) {
    update_r_->UpdateR(data_, dt);
}

// DEBUG
void Entity::Display(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLineF(
        renderer, data_.r.x - 8, data_.r.y, data_.r.x + 8, data_.r.y);
    SDL_RenderDrawLineF(
        renderer, data_.r.x, data_.r.y - 8, data_.r.x, data_.r.y + 8);
}

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

}  // namespace nigemizu::models::entity
