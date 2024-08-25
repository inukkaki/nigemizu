#ifndef NIGEMIZU_MODELS_ENTITY_H_
#define NIGEMIZU_MODELS_ENTITY_H_

#include "models/math.h"

namespace nigemizu::models::entity {

namespace impl {

namespace math = nigemizu::models::math;

}  // namespace impl

struct Data {
    impl::math::Vector2D r_;  // px
    impl::math::Vector2D v_;  // px frame-1
    impl::math::Vector2D a_;  // px frame-2
};

}  // namespace nigemizu::models::entity

#endif  // NIGEMIZU_MODELS_ENTITY_H_
