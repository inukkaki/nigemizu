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
    impl::math::Vector2D v;  // px s-1
    impl::math::Vector2D a;  // px s-2
};

class UpdateRDelegate {
public:
    virtual void UpdateR(Data& self, float dt) const = 0;
};

class NotUpdateR final : public UpdateRDelegate {
public:
    void UpdateR(Data& self, float dt) const override { /* NO-OP */ }
};

class AddVToR final : public UpdateRDelegate {
public:
    void UpdateR(Data& self, float dt) const override;
};

inline constexpr NotUpdateR kNotUpdateR;
inline constexpr AddVToR kAddVToR;

class Entity {
public:
    Entity(const Data& data,
           const UpdateRDelegate& update_r)
        : data_(data),
          update_r_(&update_r) {}
    ~Entity() {}

    void UpdateR(float dt);

    // DEBUG
    void Display(SDL_Renderer* renderer) const;

private:
    Data data_;

    const UpdateRDelegate* update_r_;
};

}  // namespace nigemizu::models::entity

#endif  // NIGEMIZU_MODELS_ENTITY_H_
