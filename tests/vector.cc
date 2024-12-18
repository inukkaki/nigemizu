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
    using nigemizu::models::math::Vector2D;
    Vector2D zero;
    Vector2D v1(0.5f, -2.5f);
    Vector2D v2(-1.2f, -6.0f);

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

    PrintVector2D(+Vector2D(-1.0f, -2.0f), "+Vector2D(-1.0f, -2.0f)");
    PrintVector2D(-Vector2D(-1.0f, -2.0f), "-Vector2D(-1.0f, -2.0f)");
    std::cout << std::endl;

    PrintVector2D(v1, "v1");
    PrintVector2D(v2, "v2");
    PrintVector2D(v1 + v2, "v1 + v2");
    PrintVector2D(v1 - v2, "v1 - v2");
    PrintVector2D(-1.5f*v1, "-1.5f*v1");
    PrintVector2D(v1*(-1.5f), "v1*(-1.5f)");
    PrintVector2D(v1/(-0.5f), "v1/(-0.5f)");
    std::cout << std::endl;

    PrintVector2D((5*v1 - (v2 - v1)*(-5))/5, "(5*v1 - (v2 - v1)*(-5))/5");
    std::cout << std::endl;

    v1 = Vector2D(-1.5f, 2.0f);
    PrintVector2D(v1, "v1 after v1 = Vector2D(-1.5f, 2.0f)");
    v1 += Vector2D(0.5f, -1.0f);
    PrintVector2D(v1, "v1 after v1 += Vector2D(0.5f, -1.0f)");
    v1 -= Vector2D(0.5f, -1.0f);
    PrintVector2D(v1, "v1 after v1 -= Vector2D(0.5f, -1.0f)");
    v1 *= -0.5f;
    PrintVector2D(v1, "v1 after v1 *= -0.5f");
    v1 /= -0.5f;
    PrintVector2D(v1, "v1 after v1 /= -0.5f");
    std::cout << std::endl;

    PrintVector2D(v1, "v1");
    PrintVector2D(v2, "v2");
    std::cout << "v1.Length(): " << v1.Length() << std::endl;
    using nigemizu::models::math::Dot;
    std::cout << "Dot(v1): " << Dot(v1) << std::endl;
    std::cout << "Dot(v1, v2): " << Dot(v1, v2) << std::endl;
    using nigemizu::models::math::Cross;
    std::cout << "Cross(v1, v1): " << Cross(v1, v1) << std::endl;
    std::cout << "Cross(v1, v2): " << Cross(v1, v2) << std::endl;

    return 0;
}
