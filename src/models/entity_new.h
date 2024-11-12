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

    const PhysicalProperty& phys() const { return phys_; }

private:
    Positional pos_;
    PhysicalProperty phys_;
};

}  // namespace nigemizu::models::entity_new

#endif  // NIGEMIZU_MODELS_ENTITY_NEW_H_
