#include "interfaces/framerate.h"

#include <cstdint>

#include "SDL2/SDL.h"

namespace nigemizu::interfaces::framerate {

void FrameRateBalancer::SetFrameRate(int frame_rate) {
    frame_rate_ = frame_rate;
    frame_duration_ = 1000.0/frame_rate;
}

void FrameRateBalancer::SetTimer() {
    timer_.Set();
}

void FrameRateBalancer::Delay() const {
    std::uint64_t elapsed_time = timer_.GetElapsedTime();
    double delay_time = frame_duration_ - elapsed_time;
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

constexpr std::uint64_t kMeasuringPeriod = 1000ull;  // ms

}  // namespace

bool FrameRateMeasurer::MeasureFrameRate(double& measured_frame_rate) {
    bool executed = false;
    ++elapsed_frames_;
    std::uint64_t elapsed_time = timer_.GetElapsedTime();
    if (elapsed_time >= kMeasuringPeriod) {
        executed = true;
        measured_frame_rate = 1000*elapsed_frames_/elapsed_time;
        elapsed_frames_ = 0;
        timer_.Set();
    }
    return executed;
}

}  // nigemizu::interfaces::framerate
