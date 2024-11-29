#ifndef NIGEMIZU_MODELS_MATH_H_
#define NIGEMIZU_MODELS_MATH_H_

#include <memory>

#include "graphics/render.h"
#include "models/vector.h"

namespace nigemizu::models::math {

namespace impl {

namespace rndr = nigemizu::graphics::render;
namespace vctr = nigemizu::models::vector;

}  // namespace impl

enum class ShapeType : unsigned char {
    kNoShape2D,
    kLineSegment2D,
    kCircle2D,
};

struct Shape2D {
    virtual ShapeType Type() const = 0;

    virtual bool CollidesWith(
        const Shape2D& other, const impl::vctr::Vector2D& offset) const = 0;

    virtual void Render(
        const impl::vctr::Vector2D& offset,
        const impl::rndr::Plotter& plotter) const = 0;

    virtual std::unique_ptr<Shape2D> Clone() const = 0;
};

struct NoShape2D : public Shape2D {
    NoShape2D() = default;
    NoShape2D(const NoShape2D&) = default;

    ShapeType Type() const override { return ShapeType::kNoShape2D; }

    bool CollidesWith(
            const Shape2D& other,
            const impl::vctr::Vector2D& offset) const override {
        return false;
    }

    void Render(
            const impl::vctr::Vector2D& offset,
            const impl::rndr::Plotter& plotter) const override {
        /* NO-OP */
    }

    std::unique_ptr<Shape2D> Clone() const override;
};

struct LineSegment2D : public Shape2D {
    impl::vctr::Vector2D s;  // Start point
    impl::vctr::Vector2D d;  // Direction (extends to the end point)

    LineSegment2D() = default;
    LineSegment2D(const impl::vctr::Vector2D& d) : d(d) {}
    LineSegment2D(
        const impl::vctr::Vector2D& s, const impl::vctr::Vector2D& d)
        : s(s), d(d) {}
    LineSegment2D(
        const LineSegment2D& other, const impl::vctr::Vector2D& offset)
        : s(other.s + offset), d(other.d) {}
    LineSegment2D(const LineSegment2D&) = default;

    ShapeType Type() const override { return ShapeType::kLineSegment2D; }

    bool CollidesWith(
        const Shape2D& other,
        const impl::vctr::Vector2D& offset) const override;

    void Render(
        const impl::vctr::Vector2D& offset,
        const impl::rndr::Plotter& plotter) const override;

    std::unique_ptr<Shape2D> Clone() const override;

    impl::vctr::Vector2D GetEndPoint() const;
};

struct Circle2D : public Shape2D {
    impl::vctr::Vector2D c;  // Center
    float r;                 // Radius

    Circle2D() : r(0.0f) {}
    Circle2D(float r) : r(r) {}
    Circle2D(const impl::vctr::Vector2D& c, float r) : c(c), r(r) {}
    Circle2D(const Circle2D& other, const impl::vctr::Vector2D& offset)
        : c(other.c + offset), r(other.r) {}
    Circle2D(const Circle2D&) = default;

    ShapeType Type() const override { return ShapeType::kCircle2D; }

    bool CollidesWith(
        const Shape2D& other,
        const impl::vctr::Vector2D& offset) const override;

    void Render(
        const impl::vctr::Vector2D& offset,
        const impl::rndr::Plotter& plotter) const override;

    std::unique_ptr<Shape2D> Clone() const override;
};

bool DetectCollision(const LineSegment2D& ls1, const LineSegment2D& ls2);
bool DetectCollision(const LineSegment2D& ls, const Circle2D& c);
bool DetectCollision(const Circle2D& c1, const Circle2D& c2);

bool DetectCollision(
    const LineSegment2D& ls1, const LineSegment2D& ls2,
    const impl::vctr::Vector2D& offset);
bool DetectCollision(
    const LineSegment2D& ls, const Circle2D& c,
    const impl::vctr::Vector2D& offset);

bool DetectCollision(
    const Circle2D& c, const LineSegment2D& ls,
    const impl::vctr::Vector2D& offset);
bool DetectCollision(
    const Circle2D& c1, const Circle2D& c2,
    const impl::vctr::Vector2D& offset);

}  // namespace nigemizu::models::math

#endif  // NIGEMIZU_MODELS_MATH_H_
