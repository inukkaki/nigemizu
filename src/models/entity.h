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
    float mass;  // kg

    impl::math::Vector2D r;  // px
    impl::math::Vector2D v;  // px s-1
    impl::math::Vector2D a;  // px s-2

    impl::math::Vector2D external_force;  // kg px s-2
};

class UpdateADelegate {
public:
    virtual void UpdateA(Data& self) const = 0;
};

class NotUpdateA final : public UpdateADelegate {
public:
    void UpdateA(Data& self) const override { /* NO-OP */ }
};

class ApplyExternalForceToA final : public UpdateADelegate {
public:
    void UpdateA(Data& self) const override;
};

inline constexpr NotUpdateA kNotUpdateA;
inline constexpr ApplyExternalForceToA kApplyExternalForceToA;

class UpdateVDelegate {
public:
    virtual void UpdateV(Data& self, float dt) const = 0;
};

class NotUpdateV final : public UpdateVDelegate {
public:
    void UpdateV(Data& self, float dt) const override { /* NO-OP */ }
};

class AddAToV final : public UpdateVDelegate {
public:
    void UpdateV(Data& self, float dt) const override;
};

inline constexpr NotUpdateV kNotUpdateV;
inline constexpr AddAToV kAddAToV;

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
           const UpdateADelegate& update_a,
           const UpdateVDelegate& update_v,
           const UpdateRDelegate& update_r)
        : data_(data),
          update_a_(&update_a),
          update_v_(&update_v),
          update_r_(&update_r) {}
    ~Entity() {}

    void UpdateA();
    void UpdateV(float dt);
    void UpdateR(float dt);

    // DEBUG
    void Display(SDL_Renderer* renderer) const;

private:
    Data data_;

    const UpdateADelegate* update_a_;
    const UpdateVDelegate* update_v_;
    const UpdateRDelegate* update_r_;
};

}  // namespace nigemizu::models::entity

#endif  // NIGEMIZU_MODELS_ENTITY_H_
