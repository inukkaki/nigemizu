#include "models/keyboard.h"

#include <string>
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

std::string Keyboard::ToString() const {
    std::string result;
    for (int i = 0; i < kNumOfKeyCodes; ++i) {
        result.append(std::to_string(pressed_[i] ? 1 : 0));
        result.append(std::to_string(pressed_prev_[i] ? 1 : 0));
        result.append(" ");
    }
    return result;
}

}  // namespace nigemizu::models::keyboard
