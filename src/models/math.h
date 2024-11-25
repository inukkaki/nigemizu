#ifndef NIGEMIZU_MODELS_MATH_H_
#define NIGEMIZU_MODELS_MATH_H_

#include <functional>
#include <memory>

namespace nigemizu::models::math {

struct Vector2D {
    float x;
    float y;

    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    Vector2D(const Vector2D&) = default;

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

using Plotter = std::function<void(int, int)>;
using ColorSetter = std::function<void(int, int, int, int)>;

void RenderLine(
    float x0, float y0, float x1, float y1, const Plotter& plotter);
void RenderLine(
    const Vector2D& p0, const Vector2D& p1, const Plotter& plotter);

void RenderCircle(
    float center_x, float center_y, float radius, const Plotter& plotter);
void RenderCircle(const Vector2D& c, float r, const Plotter& plotter);

enum class ShapeType : unsigned char {
    kLineSegment2D,
    kCircle2D,
};

struct Shape2D {
    virtual ShapeType Type() const = 0;

    virtual bool CollidesWith(
        const Shape2D& other, const Vector2D& offset) const = 0;

    virtual void Render(
        const Vector2D& offset, const Plotter& plotter) const = 0;

    virtual std::unique_ptr<Shape2D> Clone() const = 0;
};

struct LineSegment2D : public Shape2D {
    Vector2D u;  // start point
    Vector2D v;  // end point

    LineSegment2D() = default;
    LineSegment2D(const Vector2D& u, const Vector2D& v) : u(u), v(v) {}
    LineSegment2D(const LineSegment2D&) = default;

    ShapeType Type() const override { return ShapeType::kLineSegment2D; }

    bool CollidesWith(
        const Shape2D& other, const Vector2D& offset) const override
    {
        // TODO: Define this function in models/math.cc.
        // DEBUG
        return false;
    }

    void Render(const Vector2D& offset, const Plotter& plotter) const override
    {
        // TODO: Define this function in models/math.cc.
        // ...
    }

    std::unique_ptr<Shape2D> Clone() const override
    {
        // TODO: Define this function in models/math.cc.
        // DEBUG
        return std::make_unique<LineSegment2D>();
    }
};

struct Circle2D : public Shape2D {
    Vector2D c;  // center
    float r;     // radius

    Circle2D() : r(0.0f) {}
    Circle2D(float r) : r(r) {}
    Circle2D(const Vector2D& c, float r) : c(c), r(r) {}
    Circle2D(const Circle2D&) = default;

    ShapeType Type() const override { return ShapeType::kCircle2D; }

    bool CollidesWith(
        const Shape2D& other, const Vector2D& offset) const override;

    void Render(const Vector2D& offset, const Plotter& plotter) const override;

    std::unique_ptr<Shape2D> Clone() const override;
};

}  // namespace nigemizu::models::math

#endif  // NIGEMIZU_MODELS_MATH_H_
