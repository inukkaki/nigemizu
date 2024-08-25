#include "models/math.h"

namespace nigemizu::models::math {

void Vector2D::Zero() {
    x = 0.0f;
    y = 0.0f;
}

void Vector2D::Set(float x, float y) {
    this->x = x;
    this->y = y;
}

}  // namespace nigemizu::models::math
