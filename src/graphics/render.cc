#include "graphics/render.h"

#include <cmath>

#include "models/vector.h"

namespace nigemizu::graphics::render {

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

}  // namespace nigemizu::graphics::render
