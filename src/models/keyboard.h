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

struct KeyReceptor {
    bool curr;
    bool prev;

    KeyReceptor() : curr(false), prev(false) {}
    ~KeyReceptor() {}
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
    ~Keyboard() {}

    void HandleKeyDown(SDL_Keycode key);
    void HandleKeyUp(SDL_Keycode key);

    void Update();

    std::string ToString() const;

private:
    void SetKeyMap();

    impl::KeyMap key_map_;
    impl::KeyArray pressed_;
};

}  // namespace nigemizu::models::keyboard

#endif  // NIGEMIZU_MODELS_KEYBOARD_H_
