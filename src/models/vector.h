#ifndef NIGEMIZU_MODELS_VECTOR_H_
#define NIGEMIZU_MODELS_VECTOR_H_

namespace nigemizu::models::vector {

inline constexpr float kFloatTolerance = 1e-6f;

bool EqualsZero(float x);
bool Equals(float x, float y);

struct Vector2D {
    float x;
    float y;

    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    Vector2D(const Vector2D&) = default;

    void Zero();
    void Set(float x, float y);

    float Length() const;

    bool IsParallelTo(const Vector2D& other) const;

    Vector2D& operator=(const Vector2D& rhs);

    Vector2D& operator+=(const Vector2D& rhs);
    Vector2D& operator-=(const Vector2D& rhs);
    Vector2D& operator*=(float rhs);
    Vector2D& operator/=(float rhs);
};

Vector2D operator+(const Vector2D& v);
Vector2D operator-(const Vector2D& v);

Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);
Vector2D operator*(float lhs, const Vector2D& rhs);
Vector2D operator*(const Vector2D& lhs, float rhs);
Vector2D operator/(const Vector2D& lhs, float rhs);

float Dot(const Vector2D& v);
float Dot(const Vector2D& lhs, const Vector2D& rhs);

float Cross(const Vector2D& lhs, const Vector2D& rhs);

}  // namespace nigemizu::models::vector

#endif  // NIGEMIZU_MODELS_VECTOR_H_
