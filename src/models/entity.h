#ifndef NIGEMIZU_MODELS_ENTITY_H_
#define NIGEMIZU_MODELS_ENTITY_H_

#include "models/math.h"

// DEBUG
#include "SDL2/SDL.h"

namespace nigemizu::models::entity {

namespace impl {

namespace math = nigemizu::models::math;

}  // namespace impl

struct Data {
    impl::math::Vector2D r;  // px
    impl::math::Vector2D v;  // px frame-1
    impl::math::Vector2D a;  // px frame-2
};

class Entity {
public:
    Entity(const Data& data) : data_(data) {}
    ~Entity() {}

    // DEBUG
    void Display(SDL_Renderer* renderer) const;

private:
    Data data_;
};

}  // namespace nigemizu::models::entity

#endif  // NIGEMIZU_MODELS_ENTITY_H_
