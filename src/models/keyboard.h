#ifndef NIGEMIZU_MODELS_KEYBOARD_H_
#define NIGEMIZU_MODELS_KEYBOARD_H_

#include <array>

namespace nigemizu::models::keyboard {

enum class KeyCode : unsigned char {
    kA,
    kD,
    kMax,
};

inline constexpr int kNumOfKeyCodes = static_cast<int>(KeyCode::kMax);

namespace impl {

using KeyArray = std::array<bool, kNumOfKeyCodes>;

}  // namespace impl

class Keyboard {
public:
    Keyboard() {
        pressed_.fill(false);
        pressed_prev_.fill(false);
    }
    ~Keyboard() {}

    // ...

private:
    impl::KeyArray pressed_;
    impl::KeyArray pressed_prev_;
};

}  // namespace nigemizu::models::keyboard

#endif  // NIGEMIZU_MODELS_KEYBOARD_H_
