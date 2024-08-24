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

void Keyboard::HandleKeyDown(SDL_Keycode key) {
    auto it = key_map_.find(static_cast<SDL_KeyCode>(key));
    if (it != key_map_.end()) {
        int index = it->second;
        pressed_[index].curr = true;
    }
}

void Keyboard::HandleKeyUp(SDL_Keycode key) {
    auto it = key_map_.find(static_cast<SDL_KeyCode>(key));
    if (it != key_map_.end()) {
        int index = it->second;
        pressed_[index].curr = false;
    }
}

void Keyboard::Update() {
    for (auto& pressed : pressed_) {
        pressed.prev = pressed.curr;
    }
}

std::string Keyboard::ToString() const {
    std::string result;
    for (const auto& pressed : pressed_) {
        result.append(std::to_string(pressed.curr ? 1 : 0));
        result.append(std::to_string(pressed.prev ? 1 : 0));
        result.append(" ");
    }
    return result;
}

}  // namespace nigemizu::models::keyboard
