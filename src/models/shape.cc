#include "models/shape.h"

#include <memory>

#include "graphics/render.h"
#include "models/vector.h"

namespace nigemizu::models::shape {

namespace impl {

namespace rndr = nigemizu::graphics::render;
namespace vctr = nigemizu::models::vector;

}  // namespace impl

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
        const impl::vctr::Vector2D& offset,
        const impl::rndr::Plotter& plotter) const {
    impl::rndr::RenderLine(s + offset, GetEndPoint() + offset, plotter);
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
        const impl::vctr::Vector2D& offset,
        const impl::rndr::Plotter& plotter) const {
    impl::rndr::RenderCircle(c + offset, r, plotter);
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

}  // namespace nigemizu::models::shape
