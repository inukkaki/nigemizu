#ifndef NIGEMIZU_MODELS_MATH_H_
#define NIGEMIZU_MODELS_MATH_H_

namespace nigemizu::models::math {

struct Vector2D {
    float x;
    float y;

    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    ~Vector2D() {}

    void Zero();
    void Set(float x, float y);

    float Length() const;

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

enum class ShapeType : unsigned char {
    // ...
};

struct Shape2D {
    virtual ShapeType Type() const = 0;
};

}  // namespace nigemizu::models::math

#endif  // NIGEMIZU_MODELS_MATH_H_
