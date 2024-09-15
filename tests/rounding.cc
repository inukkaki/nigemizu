// Test for rounding a float value

#include <cmath>
#include <iostream>

void RoundType1(float v) {
    std::cout << v << " -> "
        << static_cast<int>(v + 0.5f)
        << std::endl;
}

void RoundType2(float v) {
    std::cout << v << " -> "
        << static_cast<int>(v >= 0 ? v + 0.5f : v - 0.5f)
        << std::endl;
}

void RoundType3(float v) {
    std::cout << v << " -> "
        << static_cast<int>(std::floor(v + 0.5f))
        << std::endl;
}

void RoundType4(float v) {
    std::cout << v << " -> "
        << static_cast<int>(std::round(v))
        << std::endl;
}

int main() {
    std::cout << "1" << std::endl;

    RoundType1(0.0f);
    RoundType1(0.5f);
    RoundType1(0.6f);
    RoundType1(0.4f);
    RoundType1(0.49999f);

    RoundType1(-0.1f);
    RoundType1(-0.5f);
    RoundType1(-0.4f);
    RoundType1(-0.6f);
    RoundType1(-0.51f);
    RoundType1(-1.0f);
    RoundType1(-1.5f);
    std::cout << std::endl;

    std::cout << "2" << std::endl;

    RoundType2(0.0f);
    RoundType2(0.5f);
    RoundType2(0.6f);
    RoundType2(0.4f);
    RoundType2(0.49999f);

    RoundType2(-0.1f);
    RoundType2(-0.5f);
    RoundType2(-0.4f);
    RoundType2(-0.6f);
    RoundType2(-0.51f);
    RoundType2(-1.0f);
    RoundType2(-1.5f);
    std::cout << std::endl;

    std::cout << "3 (safer?)" << std::endl;

    RoundType3(0.0f);
    RoundType3(0.5f);
    RoundType3(0.6f);
    RoundType3(0.4f);
    RoundType3(0.49999f);

    RoundType3(-0.1f);
    RoundType3(-0.5f);
    RoundType3(-0.4f);
    RoundType3(-0.6f);
    RoundType3(-0.51f);
    RoundType3(-1.0f);
    RoundType3(-1.5f);
    std::cout << std::endl;

    std::cout << "4 (safest?)" << std::endl;

    for (int i = -100; i < 100; ++i) {
        RoundType3(i/100.0f);
    }

    RoundType4(-0.5001f);

    return 0;
}
