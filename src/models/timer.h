#ifndef NIGEMIZU_MODELS_TIMER_H_
#define NIGEMIZU_MODELS_TIMER_H_

#include <cstdint>

#include "SDL2/SDL.h"

namespace nigemizu::models::timer {

class SimpleTimer {
public:
    SimpleTimer() : start_time_(0ull) {}

    void Set();
    std::uint64_t GetElapsedTime() const;

private:
    std::uint64_t start_time_;
};

}  // namespace nigemizu::models::timer

#endif  // NIGEMIZU_MODELS_TIMER_H_
