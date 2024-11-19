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

    Positional() = default;
    Positional(const Positional&) = default;
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
    BaseEntity() = default;
    virtual ~BaseEntity() = default;

    const Positional& pos() const { return pos_; }

    const PhysicalProperty& phys() const { return phys_; }
    PhysicalProperty&       phys()       { return phys_; }

    void AddForce(const impl::math::Vector2D& force);

    void AssignV(const impl::math::Vector2D& v);
    void AssignR(const impl::math::Vector2D& r);

    void AddR(const impl::math::Vector2D& dr);

    void UpdateA();
    void UpdateV(float dt);
    void UpdateR(float dt);

    void RenderDebugInfo(
        const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) const;

private:
    Positional pos_;
    PhysicalProperty phys_;
};

}  // namespace nigemizu::entity::base

#endif  // NIGEMIZU_ENTITY_BASE_H_
