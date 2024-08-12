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
    ~FrameRateBalancer() {}

    void SetFrameRate(int frame_rate);

    void SetTimer();
    void Delay() const;

    void Balance();

private:
    int frame_rate_;
    double milliseconds_per_frame_;

    impl::timer::SimpleTimer timer_;
};

class FrameRateMeasurer {
public:
    FrameRateMeasurer() : elapsed_frames_(0) {}
    ~FrameRateMeasurer() {}

    void SetTimer();
    bool MeasureFrameRate(double& measured_frame_rate);

private:
    int elapsed_frames_;
    impl::timer::SimpleTimer timer_;
};

}  // nigemizu::interfaces::framerate

#endif  // NIGEMIZU_INTERFACES_FRAMERATE_H_
