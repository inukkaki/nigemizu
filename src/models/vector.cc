#include "models/vector.h"

#include <cmath>

namespace nigemizu::models::vector {

bool EqualsZero(float x) {
    return (-kFloatTolerance < x) && (x < kFloatTolerance);
}

bool Equals(float x, float y) {
    return EqualsZero(x - y);
}

void Vector2D::Zero() {
    x = 0.0f;
    y = 0.0f;
}

void Vector2D::Set(float x, float y) {
    this->x = x;
    this->y = y;
}

float Vector2D::Length() const {
    return std::sqrt(x*x + y*y);
}

bool Vector2D::IsParallelTo(const Vector2D& other) const {
    return EqualsZero(Cross(*this, other));
}

Vector2D& Vector2D::operator=(const Vector2D& rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vector2D& Vector2D::operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
}

Vector2D& Vector2D::operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    return *this;
}

Vector2D operator+(const Vector2D& v) {
    Vector2D tmp(+v.x, +v.y);
    return tmp;
}

Vector2D operator-(const Vector2D& v) {
    Vector2D tmp(-v.x, -v.y);
    return tmp;
}

Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs) {
    Vector2D tmp(lhs.x + rhs.x, lhs.y + rhs.y);
    return tmp;
}

Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs) {
    Vector2D tmp(lhs.x - rhs.x, lhs.y - rhs.y);
    return tmp;
}

Vector2D operator*(float lhs, const Vector2D& rhs) {
    Vector2D tmp(lhs*rhs.x, lhs*rhs.y);
    return tmp;
}

Vector2D operator*(const Vector2D& lhs, float rhs) {
    Vector2D tmp(lhs.x*rhs, lhs.y*rhs);
    return tmp;
}

Vector2D operator/(const Vector2D& lhs, float rhs) {
    Vector2D tmp(lhs.x/rhs, lhs.y/rhs);
    return tmp;
}

float Dot(const Vector2D& v) {
    return v.x*v.x + v.y*v.y;
}

float Dot(const Vector2D& lhs, const Vector2D& rhs) {
    return lhs.x*rhs.x + lhs.y*rhs.y;
}

float Cross(const Vector2D& lhs, const Vector2D& rhs) {
    return lhs.x*rhs.y - lhs.y*rhs.x;
}

}  // namespace nigemizu::models::vector
