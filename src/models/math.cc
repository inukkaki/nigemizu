#include "models/math.h"

#include <cmath>
#include <functional>
#include <memory>

namespace nigemizu::models::math {

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

void RenderLine(
        float x0, float y0, float x1, float y1, const Plotter& plotter) {
    // NOTE: The following assignments will be changed in the future.
    int xa = static_cast<int>(std::round(x0));
    int ya = static_cast<int>(std::round(y0));
    int xb = static_cast<int>(std::round(x1));
    int yb = static_cast<int>(std::round(y1));
    int dx = static_cast<int>( std::abs(xb - xa));
    int dy = static_cast<int>(-std::abs(yb - ya));
    int error = dx + dy;
    int sx = xa < xb ? 1 : -1;
    int sy = ya < yb ? 1 : -1;
    while (true) {
        plotter(xa, ya);
        if ((xa == xb) && (ya == yb)) { break; }
        int e2 = 2*error;
        if (e2 >= dy) { error += dy; xa += sx; }
        if (e2 <= dx) { error += dx; ya += sy; }
    }
}

void RenderLine(
        const Vector2D& p0, const Vector2D& p1, const Plotter& plotter) {
    RenderLine(p0.x, p0.y, p1.x, p1.y, plotter);
}

void RenderCircle(
        float center_x, float center_y, float radius, const Plotter& plotter) {
    // NOTE: The following assignments will be changed in the future.
    int cx = static_cast<int>(std::round(center_x));
    int cy = static_cast<int>(std::round(center_y));
    int r = static_cast<int>(std::round(radius));
    int x = -r;
    int y = 0;
    int error = 2 - 2*r;
    do {
        plotter(cx - x, cy + y);
        plotter(cx - y, cy - x);
        plotter(cx + x, cy - y);
        plotter(cx + y, cy + x);
        r = error;
        if (r <= y) { ++y; error += 2*y + 1; }
        if ((r > x) || (error > y)) { ++x; error += 2*x + 1; }
    } while (x < 0);
}

void RenderCircle(const Vector2D& c, float r, const Plotter& plotter) {
    RenderCircle(c.x, c.y, r, plotter);
}

void LineSegment2D::Render(
        const Vector2D& offset, const Plotter& plotter) const {
    RenderLine(u + offset, v + offset, plotter);
}

std::unique_ptr<Shape2D> LineSegment2D::Clone() const {
    return std::make_unique<LineSegment2D>(*this);
}

namespace {

bool DetectCollisionBetween(const Circle2D& c1, const Circle2D& c2) {
    float r = c1.r + c2.r;
    return Dot(c1.c - c2.c) <= r*r;
}

bool DetectCollisionBetween(
        const Circle2D& c1, const Circle2D& c2, const Vector2D& offset) {
    return DetectCollisionBetween(c1, Circle2D(c2.c + offset, c2.r));
}

}  // namespace

bool Circle2D::CollidesWith(
        const Shape2D& other, const Vector2D& offset) const {
    // WARN: This function includes explicit downcasts.
    bool result = false;
    switch (other.Type()) {
    case ShapeType::kCircle2D:
        result = DetectCollisionBetween(
            *this, static_cast<const Circle2D&>(other), offset);
        break;
    default:
        break;
    }
    return result;
}

void Circle2D::Render(const Vector2D& offset, const Plotter& plotter) const {
    RenderCircle(c + offset, r, plotter);
}

std::unique_ptr<Shape2D> Circle2D::Clone() const {
    return std::make_unique<Circle2D>(*this);
}

}  // namespace nigemizu::models::math
