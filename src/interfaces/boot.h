#ifndef NIGEMIZU_INTERFACES_BOOT_H_
#define NIGEMIZU_INTERFACES_BOOT_H_

#include "SDL2/SDL.h"

namespace nigemizu::interfaces::boot {

bool InitGui(SDL_Window*& window, SDL_Renderer*& renderer);
void CloseGui(SDL_Window*& window, SDL_Renderer*& renderer);

}  // namespace nigemizu::interfaces::boot

#endif  // NIGEMIZU_INTERFACES_BOOT_H_
