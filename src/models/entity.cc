#include "models/entity.h"

// DEBUG
#include "SDL2/SDL.h"

namespace nigemizu::models::entity {

// DEBUG
void Entity::Display(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLineF(
        renderer, data_.r.x - 8, data_.r.y, data_.r.x + 8, data_.r.y);
    SDL_RenderDrawLineF(
        renderer, data_.r.x, data_.r.y - 8, data_.r.x, data_.r.y + 8);
}

}  // namespace nigemizu::models::entity
