#ifndef NIGEMIZU_INTERFACES_FRAMERATE_H_
#define NIGEMIZU_INTERFACES_FRAMERATE_H_

#include "models/timer.h"

namespace nigemizu::interfaces::framerate {

namespace impl {

namespace timer = nigemizu::models::timer;

}  // namespace impl

class FrameRateBalancer {
public:
    explicit FrameRateBalancer(int frame_rate) {
        SetFrameRate(frame_rate);
    }

    void SetFrameRate(int frame_rate);

    void SetTimer();
    void Delay() const;

    void Balance();

private:
    int frame_rate_;         // s-1
    double frame_duration_;  // ms

    impl::timer::SimpleTimer timer_;
};

class FrameRateMeasurer {
public:
    FrameRateMeasurer() : elapsed_frames_(0) {}

    void SetTimer();
    bool MeasureFrameRate(double& measured_frame_rate);

private:
    int elapsed_frames_;  // s-1
    impl::timer::SimpleTimer timer_;
};

}  // nigemizu::interfaces::framerate

#endif  // NIGEMIZU_INTERFACES_FRAMERATE_H_
