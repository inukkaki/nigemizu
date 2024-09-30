#ifndef NIGEMIZU_META_BOOT_H_
#define NIGEMIZU_META_BOOT_H_

#include "SDL2/SDL.h"

namespace nigemizu::meta::boot {

bool InitGui(SDL_Window*& window, SDL_Renderer*& renderer);
void CloseGui(SDL_Window*& window, SDL_Renderer*& renderer);

}  // namespace nigemizu::meta::boot

#endif  // NIGEMIZU_META_BOOT_H_
