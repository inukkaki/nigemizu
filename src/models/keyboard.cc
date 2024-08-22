#include "models/keyboard.h"

#include <unordered_map>

#include "SDL2/SDL.h"

namespace nigemizu::models::keyboard {

void Keyboard::SetKeyMap() {
    key_map_.clear();
    std::unordered_map<SDL_KeyCode, KeyCode> code_pairs = {
        {SDLK_a, KeyCode::kA},
        {SDLK_d, KeyCode::kD},
    };
    for (const auto& [key, value] : code_pairs) {
        key_map_.insert({key, static_cast<int>(value)});
    }
}

}  // namespace nigemizu::models::keyboard
