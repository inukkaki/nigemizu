#ifndef NIGEMIZU_META_ASSERT_H_
#define NIGEMIZU_META_ASSERT_H_

#include <cassert>

#ifdef NIGEMIZU_USE_GUI_ASSERT
#include "SDL2/SDL.h"
#define NIGEMIZU_ASSERT(expression) SDL_assert(expression)
#else
#define NIGEMIZU_ASSERT(expression) assert(expression)
#endif

#endif  // NIGEMIZU_META_ASSERT_H_
