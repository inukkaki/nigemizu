#ifndef NIGEMIZU_GRAPHICS_RENDER_H_
#define NIGEMIZU_GRAPHICS_RENDER_H_

#include <functional>

#include "SDL2/SDL.h"

#include "core/utils.h"
#include "meta/assert.h"
#include "models/vector.h"

namespace nigemizu::graphics::render {

namespace impl {

namespace cutl = nigemizu::core::utils;
namespace vctr = nigemizu::models::vector;

}  // namespace impl

class Renderer {
public:
    Renderer() {
        NIGEMIZU_ASSERT(initialized_);
    }
    explicit Renderer(SDL_Renderer* renderer) : renderer_(renderer) {
        initialized_.Set();
    }

private:
    impl::cutl::InitFlag initialized_;

    SDL_Renderer* renderer_;
};

using Plotter = std::function<void(int, int)>;
using ColorSetter = std::function<void(int, int, int, int)>;

void RenderLine(
    float x0, float y0, float x1, float y1, const Plotter& plotter);
void RenderLine(
    const impl::vctr::Vector2D& p0, const impl::vctr::Vector2D& p1,
    const Plotter& plotter);

void RenderCircle(
    float center_x, float center_y, float radius, const Plotter& plotter);
void RenderCircle(
    const impl::vctr::Vector2D& c, float r, const Plotter& plotter);

}  // namespace nigemizu::graphics::render

#endif  // NIGEMIZU_GRAPHICS_RENDER_H_
