#ifndef NIGEMIZU_MODELS_TIMER_H_
#define NIGEMIZU_MODELS_TIMER_H_

#include "SDL2/SDL.h"

namespace nigemizu::models::timer {

class SimpleTimer {
public:
    SimpleTimer() : start_time_(0ull) {}

    void Set();
    unsigned long long int GetElapsedTime() const;

private:
    Uint64 start_time_;
};

}  // namespace nigemizu::models::timer

#endif  // NIGEMIZU_MODELS_TIMER_H_
