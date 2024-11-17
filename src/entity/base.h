#ifndef NIGEMIZU_ENTITY_BASE_H_
#define NIGEMIZU_ENTITY_BASE_H_

#include "models/math.h"

namespace nigemizu::entity::base {

namespace impl {

namespace math = nigemizu::models::math;

}  // namespace impl

struct Positional {
    impl::math::Vector2D r;  // px
    impl::math::Vector2D v;  // px s-1
    impl::math::Vector2D a;  // px s-2

    impl::math::Vector2D f;  // Sum of external forces; kg px s-2
};

struct PhysicalProperty {
    float mass;  // kg

    PhysicalProperty() = default;
    explicit PhysicalProperty(float mass) : mass(mass) {}
    PhysicalProperty(const PhysicalProperty&) = default;

    PhysicalProperty& operator=(const PhysicalProperty&) = default;
};

class BaseEntity {
public:
    BaseEntity() {}
    virtual ~BaseEntity() = default;

    const Positional& pos() const { return pos_; }
    Positional&       pos()       { return pos_; }

    const PhysicalProperty& phys() const { return phys_; }
    PhysicalProperty&       phys()       { return phys_; }
    void phys(const PhysicalProperty& phys) { phys_ = phys; }

    void RenderDebugInfo(
        const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) const;

private:
    Positional pos_;
    PhysicalProperty phys_;
};

}  // namespace nigemizu::entity::base

#endif  // NIGEMIZU_ENTITY_BASE_H_
