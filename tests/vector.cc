// Test for Vector2D

#include <iostream>

#include "models/math.h"

namespace impl {

namespace math = nigemizu::models::math;

}  // namespace impl

void PrintVector2D(const impl::math::Vector2D& vec, const char* label) {
    std::cout << label << ": ";
    std::cout << "x=" << vec.x << ", y=" << vec.y << " ";
    std::cout << "[" << &vec << "]" << std::endl;
}

int main() {
    impl::math::Vector2D zero;
    impl::math::Vector2D v1(0.5f, -2.5f);
    impl::math::Vector2D v2(-1.2f, -6.0f);

    PrintVector2D(zero, "zero");
    PrintVector2D(v1, "v1");
    PrintVector2D(v2, "v2");
    std::cout << std::endl;

    v1.Zero();
    PrintVector2D(v1, "v1 after v1.Zero()");
    v1.Set(0.5f, -2.5f);
    PrintVector2D(v1, "v1 after v1.Set()");

    PrintVector2D(+v1, "+v1");
    PrintVector2D(-v1, "-v1");
    std::cout << std::endl;

    PrintVector2D(
        +impl::math::Vector2D(-1.0f, -2.0f), "+Vector2D(-1.0f, -2.0f)");
    PrintVector2D(
        -impl::math::Vector2D(-1.0f, -2.0f), "-Vector2D(-1.0f, -2.0f)");

    return 0;
}