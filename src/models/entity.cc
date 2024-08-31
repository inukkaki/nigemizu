#include "models/entity.h"

// DEBUG
#include "SDL2/SDL.h"

namespace nigemizu::models::entity {

void AddAToV::UpdateV(Data& self, float dt) const {
    self.v += self.a*dt;
}

void AddVToR::UpdateR(Data& self, float dt) const {
    self.r += self.v*dt;
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

}  // namespace nigemizu::models::entity
