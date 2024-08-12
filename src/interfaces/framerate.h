#ifndef NIGEMIZU_INTERFACES_FRAMERATE_H_
#define NIGEMIZU_INTERFACES_FRAMERATE_H_

#include "models/timer.h"

namespace nigemizu::interfaces::framerate {

namespace impl {

namespace timer = nigemizu::models::timer;

}  // namespace impl

class FrameRateBalancer {
public:
    explicit FrameRateBalancer(const int& frame_rate)
        : frame_rate_(frame_rate) {}
    ~FrameRateBalancer() {}

    void SetTimer();
    void Delay() const;

    void Balance();

private:
    const int& frame_rate_;
    impl::timer::SimpleTimer timer_;
};

}  // nigemizu::interfaces::framerate

#endif  // NIGEMIZU_INTERFACES_FRAMERATE_H_
