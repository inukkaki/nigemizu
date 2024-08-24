#ifndef NIGEMIZU_MODELS_KEYBOARD_H_
#define NIGEMIZU_MODELS_KEYBOARD_H_

#include <array>
#include <string>
#include <unordered_map>

#include "SDL2/SDL.h"

namespace nigemizu::models::keyboard {

enum class KeyCode : unsigned char {
    kA,
    kD,
    kMax,
};

inline constexpr int kNumOfKeyCodes = static_cast<int>(KeyCode::kMax);

namespace impl {

using KeyMap = std::unordered_map<SDL_KeyCode, int>;
using KeyArray = std::array<bool, kNumOfKeyCodes>;

}  // namespace impl

class Keyboard {
public:
    Keyboard() {
        SetKeyMap();
        pressed_.fill(false);
        pressed_prev_.fill(false);
    }
    ~Keyboard() {}

    std::string ToString() const;

private:
    void SetKeyMap();

    impl::KeyMap key_map_;

    impl::KeyArray pressed_;
    impl::KeyArray pressed_prev_;
};

}  // namespace nigemizu::models::keyboard

#endif  // NIGEMIZU_MODELS_KEYBOARD_H_
