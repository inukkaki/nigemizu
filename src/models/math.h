#ifndef NIGEMIZU_MODELS_MATH_H_
#define NIGEMIZU_MODELS_MATH_H_

namespace nigemizu::models::math {

struct Vector2D {
    float x;
    float y;

    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    ~Vector2D() {}
};

}  // namespace nigemizu::models::math

#endif  // NIGEMIZU_MODELS_MATH_H_
