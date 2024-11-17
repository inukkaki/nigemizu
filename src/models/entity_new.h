#ifndef NIGEMIZU_MODELS_ENTITY_NEW_H_
    // TODO: Replace 'ENTITY_NEW' in this macro with 'ENTITY' later.
#define NIGEMIZU_MODELS_ENTITY_NEW_H_

#include "models/math.h"

namespace nigemizu::models::entity_new {
    // TODO: Replace 'entity_new' with 'entity' later.

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
};

class Entity {
public:
    Entity() {}

    const Positional& pos() const { return pos_; }
    Positional&       pos()       { return pos_; }

    const PhysicalProperty& phys() const { return phys_; }

    void RenderDebugInfo(
        const impl::math::Plotter& plotter,
        const impl::math::ColorSetter& color_setter) const;

private:
    Positional pos_;
    PhysicalProperty phys_;
};

}  // namespace nigemizu::models::entity_new

#endif  // NIGEMIZU_MODELS_ENTITY_NEW_H_
