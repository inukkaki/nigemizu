#ifndef NIGEMIZU_MODELS_ENTITY_H_
#define NIGEMIZU_MODELS_ENTITY_H_

#include "models/math.h"

// DEBUG
#include "models/keyboard.h"

namespace nigemizu::models::entity {

namespace impl {

// DEBUG
namespace kbd = nigemizu::models::keyboard;

namespace math = nigemizu::models::math;

}  // namespace impl

struct Data {
    float mass;  // kg

    impl::math::Vector2D r;  // px
    impl::math::Vector2D v;  // px s-1
    impl::math::Vector2D a;  // px s-2

    impl::math::Vector2D external_force;  // kg px s-2
};

class ModifyExternalForceDelegate {
public:
    virtual void ModifyExternalForce(
        Data& self, const impl::math::Vector2D& force) const = 0;
};

class NotModifyExternalForce final : public ModifyExternalForceDelegate {
public:
    void ModifyExternalForce(
            Data& self, const impl::math::Vector2D& force) const override {
        /* NO-OP */
    }
};

class AddExternalForce final : public ModifyExternalForceDelegate {
public:
    void ModifyExternalForce(
        Data& self, const impl::math::Vector2D& force) const override;
};

inline constexpr NotModifyExternalForce kNotModifyExternalForce;
inline constexpr AddExternalForce kAddExternalForce;

class GetGravityDelegate {
public:
    virtual void GetGravity(
        Data& self, const impl::math::Vector2D& g) const = 0;
};

class NotGetGravity final : public GetGravityDelegate {
public:
    void GetGravity(Data& self, const impl::math::Vector2D& g) const override {
        /* NO-OP */
    }
};

class CanGetGravity final : public GetGravityDelegate {
public:
    void GetGravity(Data& self, const impl::math::Vector2D& g) const override;
};

inline constexpr NotGetGravity kNotGetGravity;
inline constexpr CanGetGravity kCanGetGravity;

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
           const ModifyExternalForceDelegate& modify_external_force,
           const GetGravityDelegate& get_gravity,
           const UpdateADelegate& update_a,
           const UpdateVDelegate& update_v,
           const UpdateRDelegate& update_r)
        : data_(data),
          modify_external_force_(&modify_external_force),
          get_gravity_(&get_gravity),
          update_a_(&update_a),
          update_v_(&update_v),
          update_r_(&update_r) {}
    virtual ~Entity() {}

    void ModifyExternalForce(const impl::math::Vector2D& force);

    void GetGravity(const impl::math::Vector2D& g);

    void UpdateA();
    void UpdateV(float dt);
    void UpdateR(float dt);

    void RenderDebugInfo(
        const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) const;

private:
    Data data_;

    const ModifyExternalForceDelegate* modify_external_force_;

    const GetGravityDelegate* get_gravity_;

    const UpdateADelegate* update_a_;
    const UpdateVDelegate* update_v_;
    const UpdateRDelegate* update_r_;
};

class Player : public Entity {
public:
    Player(const Data& data)
        : Entity(data,
                 kAddExternalForce,
                 kCanGetGravity,
                 kApplyExternalForceToA,
                 kAddAToV,
                 kAddVToR) {}
    ~Player() override {}

    // DEBUG
    void Control(const impl::kbd::Keyboard& kbd);
};

}  // namespace nigemizu::models::entity

#endif  // NIGEMIZU_MODELS_ENTITY_H_
