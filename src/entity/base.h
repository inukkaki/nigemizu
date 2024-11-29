#ifndef NIGEMIZU_ENTITY_BASE_H_
#define NIGEMIZU_ENTITY_BASE_H_

#include <memory>

#include "meta/assert.h"
#include "models/math.h"
#include "models/vector.h"

namespace nigemizu::entity::base {

namespace impl {

namespace math = nigemizu::models::math;
namespace vctr = nigemizu::models::vector;

}  // namespace impl

struct Positional {
    impl::vctr::Vector2D r;  // px
    impl::vctr::Vector2D v;  // px s-1
    impl::vctr::Vector2D a;  // px s-2

    impl::vctr::Vector2D f;  // Sum of external forces; kg px s-2

    Positional() = default;
    Positional(const Positional&) = default;
};

struct PhysicalProperty {
    float mass;  // kg

    float drag_factor;

    PhysicalProperty() = default;
    PhysicalProperty(
        float mass,
        float drag_factor)
        : mass(mass),
          drag_factor(drag_factor) {}
    PhysicalProperty(const PhysicalProperty&) = default;
};

class BaseEntity {
public:
    BaseEntity(
        const PhysicalProperty& phys,
        std::unique_ptr<impl::math::Shape2D>&& boundary)
        : phys_(phys),
          boundary_(std::move(boundary)) {
        NIGEMIZU_ASSERT(boundary_);
    }
    virtual ~BaseEntity() = default;

    const Positional& pos() const { return pos_; }

    const PhysicalProperty& phys() const { return phys_; }
    PhysicalProperty&       phys()       { return phys_; }

    impl::vctr::Vector2D CalcGravity(const impl::vctr::Vector2D& g) const;
    impl::vctr::Vector2D CalcDrag(float fluid_factor) const;

    void AddForce(const impl::vctr::Vector2D& force);

    void AssignV(const impl::vctr::Vector2D& v);
    void AssignR(const impl::vctr::Vector2D& r);

    void AddR(const impl::vctr::Vector2D& dr);

    void UpdateA();
    void UpdateV(float dt);
    void UpdateR(float dt);

    bool CollidesWith(const BaseEntity& other) const;

    void RenderDebugInfo(
        const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) const;

private:
    Positional pos_;
    PhysicalProperty phys_;

    std::unique_ptr<impl::math::Shape2D> boundary_;
};

}  // namespace nigemizu::entity::base

#endif  // NIGEMIZU_ENTITY_BASE_H_
