#include "interfaces/framerate.h"

#include "SDL2/SDL.h"

namespace nigemizu::interfaces::framerate {

void FrameRateBalancer::SetTimer() {
    timer_.Set();
}

void FrameRateBalancer::Delay() const {
    unsigned long long int elapsed_time = timer_.GetElapsedTime();
    double delay_time = 1000.0/frame_rate_ - elapsed_time;
    if (delay_time > 0.0) {
        SDL_Delay(static_cast<int>(delay_time));
    }
}

void FrameRateBalancer::Balance() {
    Delay();
    SetTimer();
}

void FrameRateMeasurer::SetTimer() {
    timer_.Set();
}

namespace {

constexpr unsigned long long int kMeasuringPeriod = 1000;  // ms

}  // namespace

bool FrameRateMeasurer::MeasureFrameRate(double& measured_frame_rate) {
    bool executed = false;
    ++elapsed_frames_;
    unsigned long long int elapsed_time = timer_.GetElapsedTime();
    if (elapsed_time >= kMeasuringPeriod) {
        executed = true;
        measured_frame_rate = 1000*elapsed_frames_/elapsed_time;
        elapsed_frames_ = 0;
        timer_.Set();
    }
    return executed;
}

}  // nigemizu::interfaces::framerate
