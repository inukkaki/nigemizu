// Test for Vector2D

#include <iostream>

#include "models/math.h"

namespace impl {

namespace math = nigemizu::models::math;

}  // namespace impl

void PrintVector2D(const impl::math::Vector2D& vec, const char* label) {
    std::cout << label << ": ";
    std::cout << "x=" << vec.x << ", y=" << vec.y << std::endl;
}

int main() {
    impl::math::Vector2D zero;
    impl::math::Vector2D v1(0.5f, -2.5f);
    impl::math::Vector2D v2(-1.2f, -6.0f);

    PrintVector2D(zero, "zero");
    PrintVector2D(v1, "v1");
    PrintVector2D(v2, "v2");

    return 0;
}
