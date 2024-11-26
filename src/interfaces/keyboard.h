#ifndef NIGEMIZU_INTERFACES_KEYBOARD_H_
#define NIGEMIZU_INTERFACES_KEYBOARD_H_

#include <array>
#include <string>
#include <unordered_map>

#include "SDL2/SDL.h"

namespace nigemizu::interfaces::keyboard {

enum class KeyCode : unsigned char {
    kZ,
    kUp,
    kLeft,
    kRight,
    kDown,
    kMax,
};

struct KeyReceptor {
    bool curr;
    bool prev;

    KeyReceptor() : curr(false), prev(false) {}
};

namespace impl {

using KeyMap = std::unordered_map<SDL_KeyCode, int>;
using KeyArray = std::array<KeyReceptor, static_cast<int>(KeyCode::kMax)>;

}  // namespace impl

class Keyboard {
public:
    Keyboard() {
        SetKeyMap();
    }

    void Clear();

    void HandleKeyDown(SDL_Keycode key);
    void HandleKeyUp(SDL_Keycode key);

    void Update();

    bool Presses(KeyCode key) const;
    bool Pressing(KeyCode key) const;
    bool Releases(KeyCode key) const;

    std::string ToString() const;

private:
    void SetKeyMap();

    impl::KeyMap key_map_;
    impl::KeyArray pressed_;
};

}  // namespace nigemizu::interfaces::keyboard

#endif  // NIGEMIZU_INTERFACES_KEYBOARD_H_
