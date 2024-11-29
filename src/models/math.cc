#include "models/math.h"

#include <cmath>
#include <functional>
#include <memory>

#include "models/vector.h"

namespace nigemizu::models::math {

namespace impl {

namespace vctr = nigemizu::models::vector;

}  // namespace impl

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
        const impl::vctr::Vector2D& p0, const impl::vctr::Vector2D& p1,
        const Plotter& plotter) {
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

void RenderCircle(
        const impl::vctr::Vector2D& c, float r, const Plotter& plotter) {
    RenderCircle(c.x, c.y, r, plotter);
}

std::unique_ptr<Shape2D> NoShape2D::Clone() const {
    return std::make_unique<NoShape2D>(*this);
}

bool LineSegment2D::CollidesWith(
        const Shape2D& other, const impl::vctr::Vector2D& offset) const {
    // WARN: This function includes explicit downcasts.
    bool collides = false;
    switch (other.Type()) {
    case ShapeType::kLineSegment2D:
        collides = DetectCollision(
            *this, static_cast<const LineSegment2D&>(other), offset);
        break;
    case ShapeType::kCircle2D:
        collides = DetectCollision(
            *this, static_cast<const Circle2D&>(other), offset);
        break;
    default:
        break;
    }
    return collides;
}

void LineSegment2D::Render(
        const impl::vctr::Vector2D& offset, const Plotter& plotter) const {
    RenderLine(s + offset, GetEndPoint() + offset, plotter);
}

std::unique_ptr<Shape2D> LineSegment2D::Clone() const {
    return std::make_unique<LineSegment2D>(*this);
}

impl::vctr::Vector2D LineSegment2D::GetEndPoint() const {
    return s + d;
}

bool Circle2D::CollidesWith(
        const Shape2D& other, const impl::vctr::Vector2D& offset) const {
    // WARN: This function includes explicit downcasts.
    bool collides = false;
    switch (other.Type()) {
    case ShapeType::kLineSegment2D:
        collides = DetectCollision(
            *this, static_cast<const LineSegment2D&>(other), offset);
        break;
    case ShapeType::kCircle2D:
        collides = DetectCollision(
            *this, static_cast<const Circle2D&>(other), offset);
        break;
    default:
        break;
    }
    return collides;
}

void Circle2D::Render(
        const impl::vctr::Vector2D& offset, const Plotter& plotter) const {
    RenderCircle(c + offset, r, plotter);
}

std::unique_ptr<Shape2D> Circle2D::Clone() const {
    return std::make_unique<Circle2D>(*this);
}

bool DetectCollision(const LineSegment2D& ls1, const LineSegment2D& ls2) {
    bool collides = false;
    if (!ls1.d.IsParallelTo(ls2.d)) {
        impl::vctr::Vector2D s = ls2.s - ls1.s;
        float cross_s_d1 = Cross(s, ls1.d);
        float cross_s_d2 = Cross(s, ls2.d);
        float cross_d1_d2 = Cross(ls1.d, ls2.d);
        float t1 = cross_s_d2/cross_d1_d2;
        float t2 = cross_s_d1/cross_d1_d2;
        collides = (
            ((0.0f < t1) && (t1 < 1.0f)) && ((0.0f < t2) && (t2 < 1.0f))
        );  // NOTE: Lenient detection.
    }
    return collides;
}

bool DetectCollision(const LineSegment2D& ls, const Circle2D& c) {
    bool collides = false;
    impl::vctr::Vector2D v1 = c.c - ls.s;
    impl::vctr::Vector2D v2 = c.c - ls.GetEndPoint();
    float dist = std::abs(Cross(ls.d, v1))/ls.d.Length();
    if (dist < c.r) {  // NOTE: Lenient detection.
        collides = (
            (Dot(ls.d, v1)*Dot(ls.d, v2) < 0.0f)  // NOTE: Lenient detection.
            || (v1.Length() < c.r)  // NOTE: Lenient detection.
            || (v2.Length() < c.r)  // NOTE: Lenient detection.
        );
    }
    return collides;
}

bool DetectCollision(const Circle2D& c1, const Circle2D& c2) {
    float r = c1.r + c2.r;
    return Dot(c1.c - c2.c) < r*r;  // NOTE: Lenient detection.
}

bool DetectCollision(
        const LineSegment2D& ls1, const LineSegment2D& ls2,
        const impl::vctr::Vector2D& offset) {
    return DetectCollision(ls1, LineSegment2D(ls2.s, offset));
}

bool DetectCollision(
        const LineSegment2D& ls, const Circle2D& c,
        const impl::vctr::Vector2D& offset) {
    return DetectCollision(ls, Circle2D(c, offset));
}

bool DetectCollision(
        const Circle2D& c, const LineSegment2D& ls,
        const impl::vctr::Vector2D& offset) {
    return DetectCollision(LineSegment2D(ls, offset), c);
}

bool DetectCollision(
        const Circle2D& c1, const Circle2D& c2,
        const impl::vctr::Vector2D& offset) {
    return DetectCollision(c1, Circle2D(c2, offset));
}

}  // namespace nigemizu::models::math
